# Objetivos
Familiarizarse con OpenMP mediante la realización de ejercicios tipo. En esta práctica no será necesario el uso de Intel Advisor.

# Comparación y Análisis
En cada uno de los ejercicios se va a preguntar que se comparen los tiempos de las distintas soluciones planteadas, para ello es importante 
que se tenga claro qué se considera como solución. Para empezar una solución será considerada como todo aquel programa que esté paralelizado y 
cuyo resultado sea el mismo que el del programa secuencial, si por ejemplo, paralelizamos un programa que calcule el número mayor de una serie
de números y el número mayor obtenido no es el mismo que el de su versión secuencial, significaría que la paralelización se ha realizado de forma errónea.
Es importante que antes de considerar una solución para tomar los tiempos de ejecución os aseguréis de que la paralelización es correcta.

A la hora de comparar soluciones hay una serie de variables que pueden modificar el tiempo que tarda en ejecutarse el programa, estas son las
siguientes:
- Número de hilos usados
- Directivas usadas para la sincronización de hilos (siempre que puedan usarse en el problema, no todas las directivas son aplicables en todos los casos)
- Reparto del trabajo

Para que la tarea de comparación no sea excesivamente costosa, dado que puede llegar a haber una gran cantidad de combinaciones, es recomendable
centrarse en una única variable de las comentadas anteriormente, por ejemplo, comparar primero todas las directivas y una vez que sabemos
qué directiva funciona mejor, pasar a observar que ocurre si cambiamos el número de hilos usados. Los cambios en el reparto de trabajo se recomienda estudiarlos al final, dado que implican menor impacto que las otras dos variables.

Para realizar la comparación de tiempo es recomendable hacer uso de una tabla, donde los resultados sean observables de un vistazo y a continuación
explicar las conclusiones que se obtienen de los mismos.

# Ejercicio 1
Desarrollar un programa secuencial que obtenga el mayor y el menor de los componentes de un vector.
A continuación, paralelizar el programa anterior usando las diferentes directivas de OpenMP que se ajusten al problema así como modificando
el número de hilos.
Analizar y comparar los tiempos de las diferentes soluciones que propongas para resolver el problema, así como el de la solución secuencial.
Con el fin de realizar estos análisis se recomienda que se realice una tabla, indicando la directiva usada, el número de hilos y el tiempo que
ha tardado dicha solución.

Realiza los cambios en results/task1/ ahí puedes crear un README.md con los análisis y guardar los diferentes códigos fuente.

# Ejercicio 2
Paraleliza el código [sumavector.cpp](src/sumavector.cpp) mediante OpenMP. Puedes proponer varias soluciones con distintas directivas.
Analiza y compara los resultados obtenidos en cada uno de ellos usando una tabla donde indiques tipo de solución.

Realiza los cambios en el código fuente en results/task2/ ahí puedes crear un README.md con los análisis y guardar las soluciones propuestas.

# Ejercicio 3
Paraleliza el código [pi.cpp](src/pi.cpp) mediante OpenMP. Puedes proponer varias soluciones.
Analiza y compara los resultados obtenidos en cada uno de ellos.
Es posible que para poder paralelizar correctamente debas realizar algún cambio en el propio algoritmo debido a dependencias entre iteraciones del bucle.

Realiza los cambios en el código fuente en results/task3/ ahí puedes crear un README.md con los análisis y guardar las soluciones propuestas.

----

# Objetives
Get familiar with OpenMP through the completion of several exercises.

# Comparison and Analysis
For each exercise, participants will be asked to compare the execution times of the proposed solutions. It is crucial to understand the definition of a solution in this context. Initially, a program is deemed a solution if it is parallelized, and its outcome is identical to its sequential counterpart. For instance, if a program is parallelized to calculate the maximum number in a series, and the resulting maximum number differs from the one derived from its sequential version, it would imply incorrect parallelization.

When comparing solutions, various factors may affect a program’s execution time:

* Number of threads used
* Directives employed (as long as they can be applied to the problem, as not all directives are universally applicable)
* Work distribution
 
To prevent the comparison task from being overly burdensome, as there may be numerous possible combinations, it is advisable to focus on a single variable mentioned above. For example, start by comparing all directives, then, once the best directive is identified, proceed to examine the effects of altering the number of threads used. It is recommended to analyze changes in work distribution lastly, as they have less impact than the other two factors.

For time comparison, consider utilizing a table where results can be easily viewed at a glance. Subsequently, elaborate on the conclusions drawn from these results.

# Exercise 1
Develop a sequential program that identifies the maximum and minimum values within a vector's components. Next, parallelize the program using various OpenMP directives applicable to the problem, and by modifying the number of threads used. Analyze and compare the execution times of the different solutions you propose to the problem, as well as the execution time of the sequential solution. To facilitate this analysis, consider creating a table indicating the directive used, number of threads, and execution time of each solution.

Make the modifications in results/task1/. In this directory, you can create a README.md with your analysis and store the different source codes.

# Exercise 2
Parallelize the code [sumavector.cpp](src/sumavector.cpp) using OpenMP. You can propose multiple solutions using different directives. Analyze and compare the results obtained from each solution using a table where you indicate the type of solution implemented.

Make changes to the source code in results/task2/. In this directory, you can create a README.md with your analysis and store the proposed solutions.

# Exercise 3
Parallelize the code pi.cpp using OpenMP. You are free to propose various solutions. Analyze and compare the results obtained from each solution. You may need to make changes to the algorithm itself to correctly parallelize it, due to dependencies between loop iterations.

Make changes to the source code in results/task3/. In this directory, you can create a README.md with your analysis and store the proposed solutions.
