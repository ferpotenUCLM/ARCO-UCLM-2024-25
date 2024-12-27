# Task4
The objective of this task was to modify a program in SYCL to ensure that operations on a shared array are performed correctly and in the proper order, avoiding concurrency problems. Three different solutions were implemented using events, in-order queues, and explicit waits.

## Initial Problem
The original code performs parallel operations on a shared array without ensuring the order of execution, which can lead to incorrect results due to the lack of explicit dependencies. In a parallel environment, tasks can be executed in any order, which can cause data inconsistencies.

## Solution 1: Dependencies through Events
In this solution, the events returned by each kernel dispatch are captured and used to establish explicit dependencies between tasks. Each task is submitted to the queue with `q.submit`, and the returned event is captured. `h.depends_on` is then used to establish explicit dependencies between tasks, ensuring that they are executed in the correct order. Finally, we wait for the last event to complete with `e3.wait()`.

**Advantages:**
- Allows fine control over the order of execution of tasks.
- It is flexible and can adapt to different dependency patterns.

**Disadvantages:**
- Can be more complex to implement and understand, especially in large programs.

## Solution 2: Dependencies using `in_order_queue`
In this solution, a queue with the `in_order` property is used to ensure that tasks are executed in the order in which they are submitted. Creating the queue with `property::queue::in_order()` ensures that each task runs only after the previous task has finished.

**Advantages:**
- Simplifies code by eliminating the need to handle explicit events and dependencies.
- It is easy to implement and understand.

**Disadvantages:**
- Less flexible than using events, since all tasks must follow a strict order.

## Solution 3: Dependencies using `wait()`
In this solution, the `wait()` function is used after each kernel dispatch to ensure that each task completes before the next one begins. This ensures that tasks are executed in the correct order, as each task waits for the previous one to finish before starting.

**Advantages:**
- Very easy to implement and understand.
- Ensures a clear and predictable order of execution.

**Disadvantages:**
- May introduce overhead due to explicit waits, which may impact performance in some cases.

## Conclusion
The three solutions ensure that operations on the shared array are performed in the correct order, avoiding concurrency problems. Each approach has its own advantages and can be chosen depending on the specific needs of the project. The choice between these methods will depend on factors such as the complexity of the program, the need for flexibility, and the impact on performance.

