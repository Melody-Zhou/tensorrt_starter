#include <stdio.h>
#include <cuda_runtime.h>

#include "utils.hpp"
#include "timer.hpp"
#include "matmul.hpp"


int seed;
int main(){
    Timer timer;

    int width     = 1<<12; // 4,096
    int low       = 0;
    int high      = 1;
    int size      = width * width;
    int blockSize = 16;
    bool statMem  = true;
    char str[100];

    float* h_matM = (float*)malloc(size * sizeof(float));
    float* h_matN = (float*)malloc(size * sizeof(float));
    float* h_matP = (float*)malloc(size * sizeof(float));
    float* d_matP = (float*)malloc(size * sizeof(float));
    
    // seed = (unsigned)time(NULL);
    seed = 1;
    initMatrix(h_matM, size, low, high, seed);
    seed += 1;
    initMatrix(h_matN, size, low, high, seed);
    
    LOG("Input size is %d x %d", width, width);
    /* GPU warmup */
    timer.start_gpu();
    MatmulOnDevice(h_matM, h_matN, h_matP, width, blockSize);
    timer.stop_gpu();
    timer.duration_gpu("matmul in gpu(warmup)");

    return 0;
}
