#include "FitnessCUDA.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

using namespace geneticalgorithm;

__global__ void deviceCode(Population &population, Parameters params) {
	unsigned int i = blockDim.x * blockIdx.x + threadIdx.x;
	population[i].setFitnessInfo(fitness::evaluateCUDA(population[i], params));
}

__host__ void geneticalgorithm::evaluateWithCUDA(Population &population, Parameters params) {
	int numElements = population.chromosomes().size();
	Population devPop;
	cudaMemcpy(&devPop, &population, sizeof(Population), cudaMemcpyHostToDevice);
	deviceCode<<<1, numElements>>> (devPop, params);
	cudaMemcpy(&population, &devPop, sizeof(Population), cudaMemcpyDeviceToHost);
	cudaFree(&devPop);
}