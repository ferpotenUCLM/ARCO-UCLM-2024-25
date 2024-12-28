#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

#include "Configurations.h"
#include "LBL_FAD_Transform_Operations.h"
#include "Utils.h"
#include "advisor-annotate.h"

#include <CL/sycl.hpp>
using namespace cl::sycl;
#include <chrono>

// --- Function Signatures
void read_Integer_Matrix(char* inputFileName, unsigned short *input_img);
void write_txt_file(char* OutputFileName, bool *data, unsigned int size);
void runDetector(unsigned short *input_img, char* OutputFileName,sycl::queue& q);

int main(int argc, char* argv[]) {
    bool GPU_is_available = false;
    bool Nvidia_GPU_is_available = false;
    device selected_device;//PRIORIZAMOS SI TENEMOS UNA GPU DE NVIDIA PERO SI NO, COMO EN MI CASO, TIRAMOS DEL
    // PROCESADOR DE INTEL
        // Check for Nvidia GPU
        for (const auto& dev : device::get_devices(info::device_type::gpu)) {
            if (dev.get_info<info::device::vendor>().find("NVIDIA") != std::string::npos)  {
                selected_device = dev;
                Nvidia_GPU_is_available = true;
                GPU_is_available = true;
                break;
            }
        }

        // If no Nvidia GPU, check for intel CPU
        if (!Nvidia_GPU_is_available) {
            for (const auto& dev : device::get_devices(info::device_type::cpu)) {
                if (dev.get_info<info::device::vendor>().find("Intel") != std::string::npos) {
                    selected_device = dev;
                    GPU_is_available = true;
                    break;
                }
            }
        }
    
    auto q = GPU_is_available ? queue(selected_device) : queue(host_selector());
    std::cout << "After checking for a GPU, we are running on:\n"
              << q.get_device().get_info<info::device::name>() << "\n";


  mkdir(OUTPUT_DIR, 0777);

  // Input Img
  unsigned short *input_img;
  input_img = (unsigned short *)malloc(sizeof(unsigned short)*IMAGE_SIZE);

  // Read the Img
  read_Integer_Matrix((char*)INPUT_FILE_NAME, input_img);

  // Run the detector
  runDetector(input_img, (char*)OUTPUT_FILE_NAME,q);

  cout << "--- Finished OK ---" << std::endl;

  free(input_img);

  return 0;
}


void read_Integer_Matrix(char* inputFileName, unsigned short *input_img)
{
  FILE * inputFile = fopen(inputFileName, "r+b");

  int numberOfReadElement = 0;
  int bytesPerElement = 2;

  unsigned short readElement;

  while ( numberOfReadElement < IMAGE_SIZE) {
    fread(&readElement, bytesPerElement, 1, inputFile);
    input_img[numberOfReadElement] = (unsigned short)readElement;
    numberOfReadElement++;
  }
  fclose (inputFile);
}


void write_txt_file(char* OutputFileName, bool *data, unsigned int size)
{
  stringstream outputFilename;
  outputFilename << OUTPUT_DIR << "/" << OUTPUT_FILE_NAME;
  ofstream outputFile;
  outputFile.open(outputFilename.str(), std::ios::app);
  for(unsigned int _it=0; _it != size; _it++)
    outputFile << data[_it] << std::endl;
  outputFile.close();
}


// Function for executing the process
void runDetector(unsigned short *input_img, char* OutputFileName,sycl::queue &q)
{
  // Initialize and declare the variables
  unsigned int nBlocks = (COLUMNS*LINES) / BLOCK_SIZE;
  unsigned int nInputElementsPerBlock = BLOCK_SIZE*BANDS;

  unsigned short input_block[BLOCK_SIZE * BANDS];
  unsigned short bg_indexes[BLOCK_SIZE * BANDS];
  unsigned short bg_block[BLOCKS_BACKGROUND * MAX_ENDMEMBERS_PER_BLOCK];
  unsigned int n_indexes=0;

  unsigned int inputIndex = 0;
  unsigned int blockIndex = 0;


  //-----------
  // Stage 1: Background
  //-----------
#ifdef VERBOSE
  cout << ":: Stage 1: Background :: " << endl;
#endif
ANNOTATE_SITE_BEGIN("First stage block for");
auto inicio = chrono::high_resolution_clock::now();
  for(; blockIndex < BLOCKS_BACKGROUND; blockIndex++){
  ANNOTATE_ITERATION_TASK("for body");
    for(unsigned int elementIndex=0; elementIndex<nInputElementsPerBlock; elementIndex++){
      input_block[ elementIndex ] = input_img[ inputIndex + elementIndex ];
    }
    inputIndex += nInputElementsPerBlock;

    LBL_FAD_Stage1(blockIndex, input_block, n_indexes, bg_indexes, bg_block,q);
  }
auto fin = chrono::high_resolution_clock::now();
chrono::duration<double> elapsed = fin - inicio;
cout << "STAGE 1 : " << elapsed.count() << "s. " << std::endl;
ANNOTATE_SITE_END();
  //-------------------


  //-----------
  //Stage2: Background stimation
  //-----------
#ifdef VERBOSE
  cout << ":: Stage 2: Background stimation :: " << endl;
#endif
  auto inicio2 = chrono::high_resolution_clock::now();
  long long tau = 0;
  unsigned char numQU = 0;
  int qMatrix[MAX_NUMQU][BANDS];
  int uMatrix[MAX_NUMQU][BANDS];
  int centroid[BANDS];


  for(unsigned int itIndex = 0; itIndex < n_indexes; itIndex++){
    for(unsigned int itBands=0; itBands<BANDS; itBands++){
      input_block[ itIndex*BANDS+itBands ] = input_img[ bg_block[itIndex]*nInputElementsPerBlock + bg_indexes[itIndex]*BANDS + itBands ];
    }
  }
  ANNOTATE_SITE_BEGIN("LBL_FAD_Stage2");
  ANNOTATE_TASK_BEGIN("LBL_FAD_Stage2");
    LBL_FAD_Stage2(input_block, centroid, qMatrix, uMatrix, numQU, tau, n_indexes,q);
    auto fin2 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed2 = fin2 - inicio2;
    cout << "STAGE 2: " << elapsed2.count() << "s. " << std::endl;
  ANNOTATE_TASK_END();
ANNOTATE_SITE_END();

#ifdef VERBOSE
  cout << ":: TAU :: " << tau << endl;
  cout << ":: numQU :: " << (short) numQU << endl;
#endif
  //-------------------



  //-----------
  // Stage3: Computation of the orthogonal substage and anomalous targets
  //-----------
#ifdef VERBOSE
  cout << ":: Stage 3: AD Map :: " << endl;
#endif
  auto inicio3 = chrono::high_resolution_clock::now();
  bool block_ad_map[BLOCK_SIZE];
  ANNOTATE_SITE_BEGIN("Third stage block for");
  for(; blockIndex < nBlocks; blockIndex++){
    ANNOTATE_ITERATION_TASK("for body of third stage");
    // Creating the block vector
    for(unsigned int elementIndex=0; elementIndex<nInputElementsPerBlock; elementIndex++){
      input_block[ elementIndex ] = input_img[ inputIndex + elementIndex ];
    }
    inputIndex += nInputElementsPerBlock;

    LBL_FAD_Stage3_4(blockIndex, input_block, numQU, tau, centroid, qMatrix, uMatrix, block_ad_map,q);


#ifdef VERBOSE_DBG
    if (blockIndex == BLOCK_DBG || BLOCK_DBG==-1){
      stringstream outputFilename;
      outputFilename << OUTPUT_DIR << "/ad_map_b" << blockIndex << ".txt";
      ofstream outputFile;
      outputFile.open(outputFilename.str());
      for(int it=0; it !=BLOCK_SIZE; it++)
	outputFile << block_ad_map[it] << endl;
      outputFile.close();
    }
#endif

    write_txt_file(OUTPUT_FILE_NAME, block_ad_map, BLOCK_SIZE);
  }
    auto fin3 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed3 = fin3 - inicio3;
    cout << "STAGE 3: " << elapsed3.count() << "s. " << std::endl;
    chrono::duration<double> total = elapsed + elapsed2 + elapsed3;
    cout << "TOTAL: " << total.count() << std::endl;
  ANNOTATE_SITE_END();
  //-------------------
}
