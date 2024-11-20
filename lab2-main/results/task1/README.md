# Comparative Report on Serial and Parallel Programs Using OpenMP

## Serial Program

The serial program performs the following tasks:

1. **Initialization**: It sets a seed for random numbers and defines the size of the vector.
2. **Random Number Generation**: It fills a vector with random numbers between 0 and 100.
3. **Finding Maximum and Minimum**: It iterates through the vector to find the maximum and minimum values.
4. **Time Measurement**: It measures the total execution time.

**Advantages**:
- **Simplicity**: The code is easier to understand and maintain.
- **Lower Overhead**: There are no costs associated with thread creation and management.

**Disadvantages**:
- **Performance**: With larger vectors, execution time can be significantly longer since only one processor core is utilized.

## Parallel Program

The parallel program introduces OpenMP to enhance performance:

1. **Initialization**: Similar to the serial program,  it defines a  vector size (100).
2. **Random Number Generation**: Same as in the serial program.
3. **Finding Maximum and Minimum**: It uses the `#pragma omp parallel for` directive to parallelize the loop that finds the maximum and minimum.
4. **Time Measurement**: It measures the total execution time.

**Advantages**:
- **Improved Performance**: By using multiple threads (4 in this case), execution time can be significantly reduced, especially with larger vectors.
- **Scalability**: The program can better utilize system resources, which is crucial for compute-intensive applications.

**Disadvantages**:
- **Complexity**: The code can be more challenging to debug and maintain due to concurrency.
- **Race Conditions**: Modifying the `mayor` and `menor` variables by multiple threads can lead to race conditions, potentially resulting in incorrect results. Synchronization mechanisms like `critical` or `atomic` would be needed to prevent this.

## Performance Comparison

- **Execution Time**: The parallel program generally has a shorter execution time compared to the serial program, especially as the vector size increases.
- **Resource Utilization**: The parallel program uses more system resources (CPU), which can be beneficial in environments requiring rapid processing.

## Conclusion

Implementing parallelism using OpenMP in the second program can lead to significant performance improvements, particularly for tasks that can be divided into independent subtasks. However, it is crucial to manage concurrency properly to avoid synchronization issues. In summary, using OpenMP is advantageous in terms of efficiency but requires greater attention to code complexity and thread management.
