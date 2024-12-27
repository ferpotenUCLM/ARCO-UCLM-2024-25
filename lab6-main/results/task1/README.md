# Task 1
Get familiar with Intel DPC compiler.
First copy the code in [src/task1/query.cpp](../../src/task1/query.cpp) to results/task1/src and compile it with dpcpp.

## Which output do you obtain?

It shows about 4 warnings, indicating that some functionalities are obsolete.
example:
"SYCL 1.2.1 device selectors are deprecated. Please use SYCL 2020 device selectors instead."

## Which different types of selectors do we have in DPC? Can we obtain a GPU? What happens if the requested device doesn't exist?

In DPC++ (Data Parallel C++), selectors are used to choose the device on which your code will run. Here are the main types of selectors:

1. **Default Selector**: Chooses the most appropriate device available, typically prioritizing GPUs over CPUs.
   ```cpp
   queue q(default_selector{});
   ```

2. **CPU Selector**: Specifically selects a CPU device.
   ```cpp
   queue q(cpu_selector{});
   ```

3. **GPU Selector**: Specifically selects a GPU device.
   ```cpp
   queue q(gpu_selector{});
   ```

4. **Accelerator Selector**: Selects an accelerator device, such as an FPGA.
   ```cpp
   queue q(accelerator_selector{});
   ```

5. **Host Selector**: Selects the host device, which is useful for debugging.
   ```cpp
   queue q(host_selector{});
   ```

Yes, we can obtain a GPU using the `gpu_selector`. If we have a compatible GPU and the necessary drivers installed, DPC++ will use it for execution.

If the requested device does not exist, DPC++ will throw an exception. For example, if you request a GPU but none is available, you might see an error like `cl::sycl::runtime_error` with a message indicating that no device of the requested type is available, to handle this gracefully, we can use a try-catch block to fall back to a different device.`

This way, your program can continue to run even if the preferred device is not available.

It is very likely that some of the devices that can be used with DPC are not available in your PC. In that case, we would look for them in other equipment or use hardware solutions through the cloud.

## Try to obtain a GPU, if it is available in your PC, by the query.cpp program into gpu_query.cpp
gpu_query.cpp stored in results/task1/src.(my pc have only integrated intel graphics)

## How did you obtained the GPU?
Using the gpu_selector must be the way.

## Modify the program to obtain more data from the device.
In more.png attached.
