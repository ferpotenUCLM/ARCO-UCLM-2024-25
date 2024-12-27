# Task 2
Code in [src/task2/buffer.cpp](../../src/task2/buffer.cpp) should represent the following flow:
1. Initialize buffer A
2. Add to each item in A the index of the iteration
3. Initialize buffer B the same way than A
4. Compute B as the result of B multiplied by A

## Check the result and show it below
To check the result, we compile and run the program. The expected result is that buffer `B` contains the values ​​of `B` multiplied by the values ​​of `A` after all operations.

```bash
dpcpp -o buffer buffer.cpp
./buffer
```

The result is:
```
0
2
8
18
32
50
72
98
128
162
200
242
288
338
392
450
```

## Which abstraction is being used for data containers?

**buffers** (`buffer<int> A{R}, B{R};`) are being used as an abstraction for data containers. The buffers in SYCL manage memory and allow data transfer between the host and devices.

## How is the DAG being built implicitly or explicitly?

The **DAG (Directed Acyclic Graph)** is formed **implicitly**. SYCL manages dependencies between tasks automatically through the use of accessors and buffers. Dependencies are resolved based on the read and write accesses specified in the accessors.

## Enumerate all dependencies and their types
- **Kernel 1**: It has no previous dependencies.
- **Kernel 2**: Depends on the completion of **Kernel 1** because they both write to buffer `A`.
- **Kernel 3**: It has no previous dependencies.
- **Kernel 4**: Depends on the completion of **Kernel 2** (reading `A`) and **Kernel 3** (reading and writing `B`).
