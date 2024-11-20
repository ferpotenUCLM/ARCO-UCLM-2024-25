#include <stdio.h>
#include <math.h>
#include <omp.h>

int main() {
    int n, i;
    double pi16ds = 3.1415926535897932; // Pi con 16 decimales
    double sum = 0.0;
    double h, pi;
    double a, z;

    printf("Introduce la precisión del cálculo (número de intervalos > 0): ");
    scanf("%d", &n);

    a = omp_get_wtime(); // Tiempo de inicio

    h = 1.0 / (double)n; // Tamaño del intervalo

    // Usar reducción para la variable sum y manejar el cálculo en paralelo
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++) {
        // xi local al hilo, calculado para cada paso
        double xi = h * (i + 0.5); // El centro del intervalo i

        // Suma parcial de PI
        sum += (4.0 / (1.0 + xi * xi));
    }

    pi = sum * h; // Calcular el valor de pi

    // Imprimir el resultado y el error
    printf("\nEl valor aproximado de PI es %0.16f con un error de %0.16f\n", pi, fabs(pi - pi16ds));

    z = omp_get_wtime(); // Tiempo de fin
    printf("El programa ha tardado %0.10f segundos \n", z - a);

    return 0;
}

