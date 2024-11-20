/* Programa secuencial que calcula la suma de los elementos de un vector v[i] 
 * y la almacena en la variable sum */ 

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <omp.h>
#define N 50 // Probar distintos tamaños de vector 

int main() 
{ 
    int i, sum, psum = 0; 
    int v[N];    

    // Damos valores aleatorios al vector (entre 0 y 99) 
    srand (time(NULL)); // Semilla de números aleatorios 
    for (i = 0; i < N; i++) v[i] = rand()%100; 

    #pragma omp parallel num_threads(4)
    {
      double psum = 0;
      int ID = omp_get_thread_num();
      int nt = omp_get_num_threads();
      int size = (N/nt);
      int init = ID*size;
      int fin = (ID == nt - 1) ? N : init + size; // por si indivisible en último hilo toma N si no la partición si falso (condición) ? valor_si_verdadero : valor_si_falso;
      printf("id: %d ,numero_HILOS : %d ,tamaño_div: %d ,val_sum_inicio: %d , val_sum_hasta: %d \n",ID,nt,size,init,fin);
      int j;
      
    // Cálculo del sumatorio 
    #pragma omp parallel for reduction(+:psum)
    for (j=init;j< fin; j++){ psum += v[j]; }         
    
    #pragma omp critical 
    sum += psum;
    }
    // Como comprobación, se visualizan los valores del vector y la suma 
    printf("\nVector de números: \n "); 
    for (i = 0; i < N; i++) printf("%d \t",v[i]);
    
	printf("\n La suma es: %d \n\n", sum); 
	return 0;
} 
