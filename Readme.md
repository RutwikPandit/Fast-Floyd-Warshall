## Floyd Warshall Implementation in C++ and CUDA

#Build Instructions

C++ : <compiler> FloydWarshall.cpp -O3 -o FW.out
CUDA: nvcc FloydWarshall.cu -o FW -arch=sm_89 (Ada)

#Limitation

CUDA version does not support input file yet.
Generates matrix of random elements for FW algorithm

#Benchmarks (GPU)
Benchmarking on my RTX 4060 machine

Vertex Size    Time(s)
4096           2s
8192           16s
16384          128s

Almost perfect cubic scaling
