# Comparison and Analysis

## Execution Time:

The total program time is observed to be 0.13 seconds, with 0.12 seconds dedicated to vectorized loops.
CPU Time in the main loop (line 72) indicates that it is the most expensive, taking up 0.12 seconds, and is flagged as a "scalar loop", implying that it is not taking advantage of vectorization.

## Performance:

The GFLOPS (Giga Floating Point Operations Per Second) metric shows a low value of 0.42, suggesting that performance could improve if the code was better vectorized.
In the second screenshot, it is detailed that the vectorized loops achieve 0.450 GFLOPS on average, while the scalar loops barely process significant operations.

## Memory and Access:

The memory analysis in the bottom panel shows that the Trip Counts are high (300), indicating that the loop is iterated many times.
The Memory AI (Arithmetic Intensity) value for this loop is 3.025, which is moderately low. This implies that the program performs few operations per byte transferred from memory, which can be a bottleneck.

## Vectorization and Scalarity:

Intel Advisor classifies most loops as "Not Vectorized", indicating that a large portion of the code does not take advantage of SIMD instructions.
On line 69 some vectorization is achieved with AVX (Int64 data carrier), but it is not replicated on line 72, where it remains as a scalar loop. This contributes to performance losses.
