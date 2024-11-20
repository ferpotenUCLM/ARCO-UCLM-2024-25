# Comparative Report on Serial and Parallel Programs for Calculating π

## Serial Program

The serial program performs the following tasks:

1. **Initialization**: It prompts the user for the number of intervals (`n`) and initializes variables.
2. **Interval Calculation**: It calculates the width of each interval (`h`) and iterates through the intervals to compute the sum.
3. **Pi Calculation**: It computes the approximate value of π using the calculated sum.
4. **Output**: It prints the calculated value of π and the execution time.

**Advantages**:
- **Simplicity**: The code is straightforward and easy to understand.
- **Lower Overhead**: There are no costs associated with thread management, making it efficient for small tasks.

**Disadvantages**:
- **Performance Limitations**: As the number of intervals increases, the execution time can become significant since only one core is utilized.

## Parallel Program   (NESTED)

The first parallel program introduces OpenMP to enhance performance:

1. **Initialization**: Similar to the serial program, it prompts for the number of intervals and initializes variables.
2. **Parallel Execution**: It uses OpenMP to create multiple threads (4 in this case) to divide the workload.
3. **Partial Sum Calculation**: Each thread calculates a partial sum (`psum`) for its assigned segment of the intervals.
4. **Reduction**: It combines the partial sums into a final sum using an atomic operation.
5. **Output**: It prints the calculated value of π and the execution time.

**Advantages**:
- **Improved Performance**: By utilizing multiple threads, the execution time can be significantly reduced, especially for larger values of `n`.
- **Scalability**: The program can efficiently utilize available CPU resources.

**Disadvantages**:
- **Increased Complexity**: The code is more complex due to the introduction of parallelism, making it harder to debug and maintain.
- **Race Conditions**: Although it uses atomic operations to update the final sum, improper management of shared variables can lead to race conditions.

## Parallel Program  (NO NESTED)

The second parallel program simplifies the parallelization process:

1. **Initialization**: Similar to the first parallel program, it prompts for the number of intervals and initializes variables.
2. **Parallel Execution with Reduction**: It uses a single OpenMP directive to parallelize the loop and handle the reduction of the sum in one step.
3. **Pi Calculation**: It computes the value of π using the combined sum.
4. **Output**: It prints the calculated value of π and the execution time.

**Advantages**:
- **Simplicity in Parallelization**: The use of a single reduction clause simplifies the code and reduces the risk of race conditions.
- **Performance**: Like the first parallel program, it benefits from multi-threading, leading to faster execution times.

**Disadvantages**:
- **Potential Overhead**: Depending on the implementation and the number of threads, there may be some overhead associated with managing parallel execution.

## Performance Comparison

- **Execution Time**: The parallel programs (both NESTED and NO NESTED) are expected to have significantly shorter execution times compared to the serial program, especially as the number of intervals (`n`) increases. The overhead of managing threads is outweighed by the performance gains from parallel execution.
- **Resource Utilization**: The parallel programs make better use of system resources, allowing for faster computations in multi-core environments.

### Conclusion

The implementation of parallelism using OpenMP in the two parallel programs can lead to substantial performance improvements, particularly for tasks that can be divided into independent subtasks. The second parallel program demonstrates a more efficient and simpler approach to parallelization through the use of reduction, minimizing complexity while maximizing performance. In summary, while using OpenMP enhances efficiency and scalability, it also introduces complexity that requires careful handling to ensure correctness.
