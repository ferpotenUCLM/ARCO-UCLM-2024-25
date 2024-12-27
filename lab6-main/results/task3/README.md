# Task 3
code in [src/task3/mult_complex.cpp](../../src/task3/mult_complex.cpp) multiplies complex numbers using both a scalar and parallel methods.

## Step 1: Modify the code based on the comments 

**Q: Perform all the requested modifications in the code (review all the comments in it)**

1. **Get device information**:
   - In the `DpcppParallel` function, we print information about the selected device.
   ```cpp
   std::cout << "Target Device: " << q.get_device().get_info<info::device::name>() << std::endl;
   ```

2. **Configure accessors**:
   - For buffers `bufin_vect1` and `bufin_vect2`, we use `read_only` since they are read only.
   - For the `bufout_vect` buffer, use `write_only` since it is write-only.
   ```cpp
   accessor V1(bufin_vect1, h, read_only);
   accessor V2(bufin_vect2, h, read_only);
   accessor V3(bufout_vect, h, write_only);
   ```

3. **Wait for the job to finish**:
   - Add `q.wait();` after the call to `q.submit` to ensure all tasks complete before continuing.
   ```cpp
   q.wait();
   ```
   
## Step 2: Show the output result
We compile and run the modified program to verify the results.

```bash
dpcpp -o mult_complex mult_complex.cpp
./mult_complex
```

# About the Task 3

1. **Output result**:
   - The output result should show the multiplication of complex numbers in parallel and verify that the results match the scalar multiplication.(in mulocmpiled.png)

2. **Abstraction for data containers**:
   - **buffers** (`buffer<int> A{R}, B{R};`) are being used as an abstraction for data containers. The buffers in SYCL manage memory and allow data transfer between the host and devices.

3. **DAG Formation**:
   - The **DAG (Directed Acyclic Graph)** is formed **implicitly**. SYCL manages dependencies between tasks automatically through the use of accessors and buffers. Dependencies are resolved based on the read and write accesses specified in the accessors.

4. **Dependencies and type of dependencies**:
   - **Kernel 1**: It has no previous dependencies.
   - **Kernel 2**: Depends on the completion of **Kernel 1** because they both write to buffer `A`.
   - **Kernel 3**: It has no previous dependencies.
   - **Kernel 4**: Depends on the completion of **Kernel 2** (reading `A`) and **Kernel 3** (reading and writing `B`).
