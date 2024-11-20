# Paralelización con OpenMP

En base al análisis realizado en las dos tareas anteriores es momento de realizar las paralelizaciones que consideres oportunas en el código.

Para cada paralelización completa la siguiente plantilla de resultados:

## Paralelización X

### Análisis previo
Indica en qué te has basado para paralelizar esta región de código, apoya tu argumentación con capturas de Intel Advisor.

### Paralelización
Explica las modificaciones realizadas sobre el código original

¿Has tenido que modificar cómo se calcula alguna variable para evitar dependencias de tipo inter-loop?

### Análisis posterior
Compara el código original con el mejorado y realiza tablas de comparación aumentando el número de hilos.

* ¿Coinciden los resultados con el valor predecido por la herramienta?
* ¿Cómo has comparado los resultados para verificar la correción del programa paralelo?

### Resultados
Por cada mejora guarda los resultados y el código junto a su makefile en results/task3/vX donde X indica el orden en que has paralelizado.

Cada carpeta de resultados tiene que ser ejecutable, es decir, el profesor podrá realizar un make y make run en dichas carpetas
para comprobar cada mejora parcial.

## Mejora combinada
Una vez paralelizado cada región por separado, combina los resultados y completa la plantilla anterior.

---

# Parallelization with OpenMP

Based on the analysis carried out in the previous two tasks, it is time to perform the parallelizations you consider appropriate in the code.

For each parallelization, complete the following results template:

## Parallelization X

### Preliminary Analysis
Indicate what you based your decision on to parallelize this region of code, support your argument with screenshots from Intel Advisor.

### Parallelization
Explain the modifications made to the original code.

Did you have to modify how any variable is calculated to avoid inter-loop dependencies?

### Post Analysis
Compare the original code with the improved one and create comparison tables by increasing the number of threads.

* Do the results match the value predicted by the tool?
* How did you compare the results to verify the correctness of the parallel program?

### Results
For each improvement, save the results and the code along with its makefile in results/task3/vX where X indicates the order in which you parallelized.

Each results folder must be executable, meaning the professor should be able to run make and make run in those folders to check each partial improvement.

## Combined Improvement
Once each region has been parallelized separately, combine the results and complete the previous template.

# IMPROVEMENTS

The file LBL_FAD_Transform_Operations.cpp have nested loops (for) pixel move & band:

for (int pixel = 0; pixel < blockSize; pixel++) {
    for (int band = 0; band < BANDS; band++) {
        // Operaciones en Img
    }
}

Por otro lado, el archivo image.c ya tiene directivas de OpenMP, como:

#pragma omp parallel for private(pixel) num_threads(PARALLEL)
for (int i = 0; i < width * height; i++) {
    // Operaciones en los píxeles
}

Parallelization strategy for LBL_FAD_Transform_Operations.cpp:

    Identify independent loops and candidates for parallelization. For example, loops over pixels, bands or independent iterations like iter.
    Insert #pragma omp directives before loops. Make sure:
        Define private or shared variables with private and shared.
        Specify the number of threads (num_threads).
        Use scheduling strategies such as static or dynamic.



​

Loop in LBL_FAD_Transform_Operations.cpp:

for (int pixel = 0; pixel < blockSize; pixel++) {
    for (int band = 0; band < BANDS; band++) {
        Img[pixel * BANDS + band] -= projection[pixel] * qVector[band];
    }
}


## USE OF COLLAPSE :
#include <omp.h>

#pragma omp parallel for collapse(2) num_threads(PARALLEL)
for (int pixel = 0; pixel < blockSize; pixel++) {
    for (int band = 0; band < BANDS; band++) {
        Img[pixel * BANDS + band] -= projection[pixel] * qVector[band];
    }
}

## EXPLANATION:

#pragma omp parallel for: Parallelize the following loop.
collapse(2): Combines the iterations of the two loops (pixel and band) to parallelize them together, improving efficiency in nested structures.
num_threads(PARALLEL): Controls the number of threads used, defined as a constant (PARALLEL).
Shared and private variables: Be sure to declare variables like Img, projection, and qVector as shared if all threads need access to them.



Include #include <omp.h>: Added the header needed to use OpenMP.
OpenMP directives:
I added #pragma omp parallel for collapse(2) for nested loops that traverse pixels and bands.
I used num_threads(4) as an example to specify the number of threads.
Other optimizations: Applied only in clearly parallelizable loops, ensuring that iterations do not depend on each other.
