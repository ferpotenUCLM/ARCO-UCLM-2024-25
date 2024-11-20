# Tarea 4: Análisis de memoria y mejora vectorización

## Preguntas

* Compila de nuevo el programa complexmul.cpp **sin vectorizar** y genera un análisis de memoria marcando los bucles del cómputo que realizan la mutliplicación de números complejos, en concreto marca los bucles de las líneas 27 y 28 (si el análisis se demora mucho prueba a reducir el tamaño). Realiza el análisis tanto usando la interfaz gráfica de intel advisor como por línea de comandos. Además indica que comando es el que has usado para realizar el análisis por comando.

* Abre advisor y selecciona la vista "Refinement Reports".
    * ¿Qué información nos proporciona esta vista? enumera cada elemento de la tabla resumiendo el significado
    * ¿Qué comportamiento de memoria se obtiene? ¿Por qué es deseable tener un stride uniforme?
    * Mira el resultado del análisis de memoria de ambos bucles y comprueba que el stride es de 2.
        * ¿Por qué el stride tiene este valor? (Revisa los conceptos de row-order y column-order así como el orden en el que se reserva la memoria en C)
        * ¿Sobre que variables se está accediendo con un stride de 2? ¿Cómo afecta esto a la caché?
        * ¿Se te ocurre algún modo de modificar el programa, manteniendo los dos bucles y el mismo resultado, para que
        el acceso a la variable sea uniforme? Realiza la modificación y almacena el resultado en esta misma carpeta con el nombre complexmul_unit_stride.cpp.
        
* Genera un snapshot para el análisis completo (hasta los patrones de acceso a memoria) tanto para la versión con un stride de 2 como para la versión con stride unitario (ambos vectorizando el código) y llámalos respectivamente "task4a" y "task4b", añádelos a esta misma carpeta. 
    * En "task4b" ¿Cuáles son los valores de la longitud del vector y la ganancia estimada? ¿Son los resultados que se esperaban? Justifica la respuesta.
    * Comparando estas dos soluciones ¿Cuánto ha aumentado la ganancia?

* Compara los resultados del análisis task2 y task4b:
    * ¿Cuál ha sido la ganancia real del algoritmo vectorizado? ¿Ha sido menor o mayor a la estimación?
 
-----

# Task 4: Memory Analysis and Vectorization improvement

## Questions:

* Recompile the complexmul.cpp program without vectorization and generate a memory analysis, highlighting the computation loops that perform the multiplication of complex numbers. Specifically, mark the loops on lines 27 and 28 (if the analysis takes too long, consider reducing the size). Conduct the analysis using both the Intel Advisor graphical interface and the command line. Also, specify the command you used for the command-line analysis.

* Open Advisor and select the "Refinement Reports" view.

  * What information does this view provide? List each item in the table, summarizing its meaning.
  * What memory behavior is observed? Why is it desirable to have a uniform stride?
  * Examine the memory analysis results for both loops and confirm that the stride is 2.
  * Why is the stride value set at this level? (Review the concepts of row-order and column-order, as well as the order in which memory is allocated in C).
  * Which variables are being accessed with a stride of 2? How does this affect the cache?
  * Can you think of a way to modify the program, keeping the two loops and the same outcome, so that variable access is uniform? Implement the change and save the result in this same folder with the name complexmul_unit_stride.cpp.
* Generate a snapshot for the complete analysis (up to memory access patterns) for both the version with a stride of 2 and the version with a unitary stride (both vectorizing the code). Name them "task4a" and "task4b", respectively, and add them to this same folder.

  * In "task4b," what are the values for vector length and the estimated gain? Are these the expected results? Justify your answer.
  * Comparing these two solutions, by how much has the gain increased?
* Compare the analysis results of task2 and task4b:
  * What was the actual gain from the vectorized algorithm? Was it less or more than the estimate?
  
  
# ANSWERS


## 1. Non-vectorized memory compilation and analysis

We perform a memory analysis by marking the loops of lines 27 and 28.

### Command for command line analysis:

Run the following command in the terminal:


advixe-cl -collect map -- ./mapcompl.out


This will generate a memory scan. We also used the Intel Advisor graphical interface to perform the same analysis.

## 2. "Refinement Reports" view

We open Intel Advisor and select the **"Refinement Reports"** view.

- **Information Provided**: This view shows details about memory and vectorization performance. Typical items include:
  - **Memory Access Patterns**: Shows how memory is accessed.
  - **Stride**: Indicates the memory access pattern (number of memory positions skipped).
  - **Cache Utilization**: Shows how caches are used.
  - **Vectorization Opportunities**: Indicates if there are opportunities to improve vectorization.

- **Memory behavior**: A **uniform stride** is desirable because it allows more efficient access to memory, improving cache utilization and reducing cache misses.

## 3. Stride analysis
We review the memory analysis result of both loops and verify that the stride is 2.

- **Why stride is 2**: This is due to how data is stored in memory in C. In this case, we are accessing a two-dimensional array where each row contains two elements (real and imaginary). Therefore, when iterating over `c[i][REAL]` and `c[i][IMAG]`, an element in memory is skipped, resulting in a stride of 2.

- **Variables with stride of 2**: We are accessing the variables `a[i][REAL]`, `a[i][IMAG]`, `b[j][REAL]`, and `b[ j][IMAG]`. This non-uniform access can cause cache problems as it can result in a higher number of cache misses.

- **Modification for uniform access**: To modify the program and maintain the same result, we can rearrange the loops to access the data in a way that the stride is minimized. 



### 4. Generación de snapshots
Genera un snapshot para el análisis completo de ambas versiones:

- Para la versión con stride de 2:

advixe-cl -collect map -- ./mapcmpl

Guardar `task4a`.

- Para la versión con stride unitario:

advixe-cl -collect map -- ./complex

Guardar `task4b`.

Task4b 0.01 segundos más rapido que Task4a
