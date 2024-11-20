#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <omp.h>

int main() {
    // Inicializar la semilla para los números aleatorios
    std::srand(std::time(0));
    double init,end,time;
    // Tamaño del vector
    init = omp_get_wtime();
    int tamano = 100;  // Cambiar el tamaño del vector aquí
    std::vector<int> numeros(tamano);

    // Llenar el vector con números aleatorios entre 0 y 100
    for (int &num : numeros) {
        num = std::rand() % 101;
    }

    // Inicializar mayor y menor con valores extremos
    int mayor = std::numeric_limits<int>::min();
    int menor = std::numeric_limits<int>::max();

    // Recorrer el vector para encontrar el mayor y el menor
    for (int num : numeros) {
        if (num > mayor) {
            mayor = num;
        }
        if (num < menor) {
            menor = num;
        }
    }

    end = omp_get_wtime();
    time = end - init; 
    // Imprimir los números generados
    std::cout << "Números generados: ";
    for (int num : numeros) {
        std::cout << num << " ";
    }

    std::cout << std::endl;

    std::cout << "El mayor es: " << mayor << std::endl;
    std::cout << "El menor es: " << menor << std::endl;
    printf("Time of execution is %f \n",time);

    return 0;
}

