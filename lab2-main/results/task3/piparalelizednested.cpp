/* Programa serie para calcular pi */ 
#include <math.h> 
#include <stdio.h> 
#include <omp.h> 
int main() 
{  
	int n,i; 
	double a,z; 
	double pi16ds = 3.1415926535897932; // con 25 decimales 3.141592653589793238462643 
	double sum = 0.0;
	double h;double pi;

	printf("Introduce la precision del calculo (número de intervalos > 0): "); 
	scanf("%d", &n); 
	a = omp_get_wtime();
	
	h = 1.0 / (double)n; // tamaño intervalo 
	#pragma omp parallel num_threads(4)
        {
        double psum = 0;
        int ID = omp_get_thread_num();
        int nt = omp_get_num_threads();
        int size = (n/nt);
        int init = ID*size;
        int fin = init+size;
        printf("id: %d ,numero_HILOS : %d ,tamaño_div: %d ,val_sum_inicio: %d , val_sum_hasta: %d \n",ID,nt,size,init,fin);

        //division de un for en 4 chunks de codigo en este caso

	#pragma omp parallel for reduction(+:psum)
        for (i = init; i < fin; i++) {
        // xi local al hilo, calculado para cada paso
          double xi = h * (i + 0.5); // El centro del intervalo i

        // Suma parcial de PI
          psum += (4.0 / (1.0 + xi * xi));
        }

	#pragma omp atomic
        sum += psum;
        }
        
        pi = sum * h; 

	

	printf("\nEl valor aproximado de PI es %0.16f con un error de %0.16f\n", pi, fabs(pi-pi16ds)); 
        
	z = omp_get_wtime(); 

	printf("El programa ha tardado %0.10f segundos \n", z-a);
	return 0;
} 
