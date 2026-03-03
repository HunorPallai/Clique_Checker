#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "GraphCliqueCPUCode.h"
//#include "Simulation.h"
#include "Bitstream.h"
#include "MaxSLiCInterface.h"

uint64_t binomialCoefficient(const int n, const int k) {
	uint64_t result = 1;
	for (int i = 0; i < k; ++i) {
		result = result * (uint64_t)(n - i) / (uint64_t)(i + 1);
	}

	return result;
}

uint64_t unrank(const uint64_t rank, const int k, const int n) {
	uint64_t subset = 0;
	uint64_t remainingRank = rank;

	for (int element = 0; element < k; ++element) {
		int elementsToPlace = k - element;

		int pos = elementsToPlace - 1;
		bool found_pos = false;
		for (int i = pos; (i < n - element) && !found_pos; ++i) {
			uint64_t c = binomialCoefficient(i, elementsToPlace);
			if (c <= remainingRank) {
				pos = i;
			}
			else {
				found_pos = true;
			}
		}

		remainingRank -= binomialCoefficient(pos, elementsToPlace);
		subset |= (uint64_t)1 << pos;
	}

	return subset;
}

void gospersSplit(const int k, const int n, const int concurrency, GosperPartition* partitions) {
	uint64_t total = binomialCoefficient(n, k);
	uint64_t baseCount = total / (uint64_t)concurrency;
	uint64_t remainder  = total % (uint64_t)concurrency;

	for (int i = 0; i < concurrency; ++i) {
		partitions[i].count = (i < (int)remainder) ? baseCount + 1 : baseCount;
	}

	uint64_t* boundaries = (uint64_t*)malloc(concurrency * sizeof(uint64_t));
	boundaries[0] = partitions[0].count;
	for (int i = 1; i < concurrency; ++i) {
		boundaries[i] = boundaries[i - 1] + partitions[i].count;
	}

	uint64_t* boundarySubsets = (uint64_t*)malloc(concurrency * sizeof(uint64_t));
	for (int i = 0; i < concurrency; ++i) {
		boundarySubsets[i] = unrank(boundaries[i], k, n);
	}

	partitions[0].initialSubset = ((uint64_t)1 << k) - 1;
	partitions[0].limit = boundarySubsets[0];
	for (int i = 1; i < concurrency; ++i) {
		partitions[i].initialSubset = boundarySubsets[i - 1];
		partitions[i].limit = boundarySubsets[i];
	}
	partitions[concurrency - 1].limit += 1;

	free(boundaries);
	free(boundarySubsets);
}

uint64_t* generateCompleteMatrix(int n) {
	uint64_t* result = (uint64_t*)malloc(n * sizeof(uint64_t));
	memset(result, 0, n * sizeof(uint64_t));

	uint64_t bits = (n == 64) ? ~(uint64_t)0 : ((uint64_t)1 << n) - 1;
	for (int i = 0; i < n; ++i) {
		result[i] = bits;
	}

	return result;
}

uint64_t* generateAdjacencyMatrix(int n, double p) {
	uint64_t* result = (uint64_t*)malloc(n * sizeof(uint64_t));
	memset(result, 0, n * sizeof(uint64_t));

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			double r = (double)rand() / (double)RAND_MAX;

			if (r < p) {
				result[i] |= (1ULL << j);
				result[j] |= (1ULL << i);
			}
		}
	}

	return result;
}

int main(int argc, char* argv[]) {
	int n = 6;
	int k = 3;
	
	if (argc >= 3) {
		n = atoi(argv[1]);
		k = atoi(argv[2]);
	}
	
	GosperPartition* partitions = (GosperPartition*)malloc(CONCURRENCY * sizeof(GosperPartition));
	memset(partitions, 0, CONCURRENCY * sizeof(GosperPartition));
	gospersSplit(k, n, CONCURRENCY, partitions);

	printf("PartA initial subset: %lu\n", (unsigned long) partitions[0].initialSubset);
	printf("PartB initial subset: %lu\n", (unsigned long) partitions[1].initialSubset);

	uint64_t LOAD_TICK_COUNT = 64;
	uint64_t subsetCount = binomialCoefficient(n, k);
	uint64_t computeTickCount = 2 * partitions[0].count;
	uint64_t totalTickCount = computeTickCount + LOAD_TICK_COUNT;
	uint64_t* cliques = (uint64_t*) malloc(subsetCount * sizeof(uint64_t));
	uint64_t* adjMatrix = generateCompleteMatrix(n);

	max_file_t* maxfile = Bitstream_init();
	max_engine_t* engine = max_load(maxfile, "*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	max_set_ticks(actions, "MatrixLoadKernel", totalTickCount);
	max_set_uint64t(actions, "MatrixLoadKernel", "loadTickCount", LOAD_TICK_COUNT);

	max_set_ticks(actions, "GraphCliqueDFEKernel", computeTickCount);
	max_set_uint64t(actions, "GraphCliqueDFEKernel", "initialSubsetA", partitions[0].initialSubset);
	max_set_uint64t(actions, "GraphCliqueDFEKernel", "initialSubsetB", partitions[1].initialSubset);

	max_queue_input(actions, "adjMatrixRow", adjMatrix, LOAD_TICK_COUNT * sizeof(uint64_t));

	max_queue_output(actions, "cliqueCount", cliques, computeTickCount * sizeof(uint64_t));

	max_run(engine, actions);

	//Simulation(tickCount, partitions[0].initialSubset, partitions[1].initialSubset, subset, subsetCount * sizeof(uint64_t));
	
	for (uint64_t i = 0; i < subsetCount; i++)
		printf("cliqueCount[%lu] = %lu\n", (unsigned long)i, (unsigned long) cliques[i]);

	max_actions_free(actions);

	free(cliques);
	free(partitions);
	free(adjMatrix);

	return 0;
}
