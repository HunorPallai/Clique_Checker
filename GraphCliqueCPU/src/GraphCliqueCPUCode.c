#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//#include "GraphCliqueDFE.h"
#include "Simulation.h"
#include "MaxSLiCInterface.h"

uint64_t binomialCoefficient(uint64_t n, uint64_t k) {
	uint64_t result = 1;
	for (uint64_t i = 0; i < k; ++i) {
		result = result * (n - i) / (i + 1);
	}

	return result;
}

int main(int argc, char* argv[]) {
	uint64_t n = 6;
	uint64_t k = 3;
	
	if (argc >= 3) {
		n = atoi(argv[1]);
		k = atoi(argv[2]);
	}
	
	uint64_t subsetCount = binomialCoefficient(n, k);
	uint64_t tickCount = 2 * subsetCount;
	uint64_t initialSubset = (1ULL << k) - 1;
	uint64_t* subset = (uint64_t*) malloc(subsetCount * sizeof(uint64_t));

	//printf("GraphClique DFE test: n = %d, k = %d\n", n, k);
	Simulation(tickCount, initialSubset, subset, subsetCount * sizeof(uint64_t));
	//uint64_t expected = binomialCoefficient(n, k);
	
	//printf("Expected (C(%d,%d)): %lu\n", n, k, (unsigned long)expected);
	
	for (uint64_t i = 0; i < subsetCount; i++)
		printf("subset[%lu] = %lu\n", (unsigned long)i, (unsigned long) subset[i]);

	return 0;
}
