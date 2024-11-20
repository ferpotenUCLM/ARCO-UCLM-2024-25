# Tarea 1: Intel Advisor

## Preguntas
* En la vista de "Survey & Roofline" se hace referencia a Total time y self-time. ¿Qué diferencia hay entre ambas?
* Realiza un análisis de tipo Survey, accede a  la pestaña "Survey & Roofline" y haz una captura de la información (se usará
más tarde).
* Pulsa sobre roofline (dentro de Survey & Roofline) y comprueba que no aparece ningún gráfico. ¿A qué se debe?
* Haz un análisis de trip-counts y flop. ¿Qué información nueva aparece en la vista de survey? Haz una captura y comenta
los datos nuevos más relevantes.

-----------------

# Task 1: Intel Advisor

## Questions
* Within the "Survey & Roofline" view, references are made to both Total time and Self-time. What is the difference between these two terms?
* Conduct a Survey analysis, navigate to the "Survey & Roofline" tab, and capture the information displayed (this will be used later).
* Click on the roofline within the "Survey & Roofline" and observe that no chart appears. What could be the reason for this absence?
* Perform an analysis focusing on trip-counts and FLOP (Floating Point Operations). What new information is presented in the survey view? Capture this information and discuss the most pertinent new data.


# ANSWERS :

## 1. Difference between Total Time and Self-Time
- **Total Time**: Refers to the total time it takes to execute a function or a block of code, including the time spent on other functions that are called within it.
- **Self-Time**: It is the time spent exclusively on the function itself, not including the time of the functions that are called from it. In short, **Self-Time** is a measure of the time a function spends executing without considering its calls to other functions.



## 2. Survey type analysis
- Open **Intel Advisor** and select the **Survey** option.
- We run the **Survey** analysis in the application. This can be done from the command line with the following command:
 
  advixe-cl -collect survey -- <app_binary_name>
  advixe-cl -collect survey -- ./mul.out

Capture **survey**.


## 3. Roofline Chart
- When clicking on **Roofline** within **Survey & Roofline**, since no graph appears, it is because an analysis of **Trip Counts** or **FLOPs** has not been carried out. For the graph to be generated, an additional analysis needs to be run to collect this data. 


## 4. Analysis of Trip Counts and FLOPs

- After completing the analysis, we return to the **Survey** tab. Here we see new information, such as:
  - **Trip Counts**: Number of times each loop is executed.
  - **FLOPs**: Floating point operations per second, which indicate computational efficiency.
  
- We look to see if any loop has a high number of **Trip Counts** but a low number of **FLOPs**, this could indicate that there are opportunities to optimize performance.
