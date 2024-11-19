# Laboratorio 1: Toma de contacto con el entorno
El objetivo de esta práctica es que os familiaricéis con las herramientas con las que trabajaremos durante los laboratorios
de la asignatura.

# Tareas
1. Compila y ejecuta el programa matmul.cpp guardando el resultado de ejecución en results/task1/task1.txt. Para realizar la
   compilación utiliza el compilador g++ y añade las opciones del compilador -g, -O0 y -fopenmp. La opción -g añade información de depuración y es recomendable que la uséis siempre
   que vayáis a analizar el rendimiento de un programa con Intel Advisor. La opción -fopenmp enlaza las bibliotecas de OpenMP para programación paralela. La opción -O0 desactiva las optimizaciones por defecto.
2. Realiza un análisis **con los tipos Survey y Characterization (Trip Counts y FLOP)** del programa en tu PC haciendo uso de la interfaz gráfica de Intel Advisor:
    * Una vez realizado el análisis, en la parte de arriba debería observarse un warning con el siguiente mensaje 
    *"Some target modules are not compiled with optmization enabled and with version 15.0 or higher of the Intel compiler"* ¿Qué es lo que indica
      este aviso? ¿Como solucionarías este problema de modo que el warning desaparezca (es posible que no se eliminen todos los warnings)? 
      (**pista**: tiene que ver con el compilador usado, revisa los compiladores que dispones con intel oneAPI, una vez encuentres el
      adecuado será el que **debas usar para todas las prácticas, incluidas las tareas restantes de esta prática**). Guarda los resultados del análisis
      con el warning realizando un snapshot de intel advisor (importante no confundir con una captura de pantalla) con el nombre **warning** en 
      [results/task2](results/task2).
    * Recompila el código con el compilador apropiado. Guarda los resultados del análisis sin el warning realizando un snapshot de intel advisor. 
    Este snapshot se debe subir al repositorio en [results/task2](results/task2) con el nombre **snapshot**.
3. Compara y **analiza** los resultados haciendo énfasis en las medidas de tiempo, rendimiento y memoria
    * El informe se debe subir a la carpeta [results/task3](results/task3) con el nombre comparacion.md
    * El informe tiene que estar en formato markdown
4. Identifica las características clave de los sistemas sobre los que has ejecutado los análisis (procesador, memoria, caché...)
y relaciónalos con los resultados analizados
    * El informe se debe subir a la carpeta [results/task4](results/task4) con el nombre caracteristicas.md

# Participantes
**FERNANDO POTENCIANO SANTIAGO**

# Enlaces de utilidad
- [Sintaxis markdown](https://guides.github.com/features/mastering-markdown/)

---

# Laboratory 1: Getting Acquainted with the Environment
The objective of this practice is for you to become familiar with the tools we will use during the course labs.

# Tasks

1. Compile and run the program matmul.cpp, saving the execution result in results/task1/task1.txt. For the compilation, use the g++ compiler and add the compiler options -g, -O0 and -fopenmp. The -g option adds debugging information and it's advisable to use it whenever you're going to analyze a program's performance with Intel Advisor. The -fopenmp option links the OpenMP libraries for parallel programming. The switch -O0 disables default optimizations.
2. Perform an analysis with Survey and Characterization types (Trip Counts and FLOP) on your PC using the Intel Advisor graphical interface:
  * Once the analysis is done, you should see a warning at the top with the message **Some target modules are not compiled with optimization enabled and with version 15.0 or higher of the Intel compiler**. What does this warning indicate? How would you solve this problem so that the warning disappears (it might not be possible to eliminate all warnings)? (**hint**: it has to do with the compiler used, check the compilers you have with intel oneAPI, once you find the right one **you should use it for all practices, including the remaining tasks of this lab**). Save the analysis results with the warning by taking a snapshot of Intel Advisor (important not to confuse it with a screenshot) named **warning** in [results/task2](results/task2).
  * Recompile the code with the appropriate compiler. Save the analysis results without the warning by taking a snapshot of Intel Advisor. This snapshot should be uploaded to the repository in results/task2 named snapshot.
3. Compare and **analyze** the results, emphasizing time, performance, and memory measures. Upload the report to the [results/task3](results/task3) folder named comparacion.md. The report must be in markdown format.
4. Identify the key characteristics of the systems on which you have run the analyses (processor, memory, cache, etc.) and relate them to the analyzed results.
Upload the report to the [results/task4](results/task4) folder with the name caracteristicas.md.


# Participants
**FERNANDO POTENCIANO SANTIAGO**

# Useful Links

[Markdown syntax](https://guides.github.com/features/mastering-markdown/)


