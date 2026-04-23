#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

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
	int n = 43;
	int k = 5;
	
	if (argc >= 3) {
		n = atoi(argv[1]);
		k = atoi(argv[2]);
	}
	const float startTimeBeforePartition = (float)clock()/CLOCKS_PER_SEC;

	const int num_partitions = NUMBER_OF_COUNTER_KERNELS * KERNEL_INTERNAL_CONCURRENCY;
	GosperPartition* partitions = (GosperPartition*)malloc( num_partitions * sizeof(GosperPartition));
	memset(partitions, 0, num_partitions * sizeof(GosperPartition));

	gospersSplit(k, n, num_partitions, partitions);

	for (int i = 0; i < num_partitions; ++i) {
		printf("Part %d initial subset: %lu, count: %lu, limit: %lu\n", i,
				(unsigned long) partitions[i].initialSubset,
				(unsigned long) partitions[i].count,
				(unsigned long) partitions[i].limit);
	}

	uint64_t subsetCount = binomialCoefficient(n, k);
	printf("Binomial Coefficient n=%d, k=%d: %lu\n", n, k, (unsigned long) subsetCount);

	uint64_t maxComputeTickCount = KERNEL_INTERNAL_CONCURRENCY * partitions[0].count;
	uint64_t totalTickCount = maxComputeTickCount + LOAD_TICK_COUNT;

	uint64_t* cliqueCounts = (uint64_t*) malloc(KERNEL_INTERNAL_CONCURRENCY *sizeof(uint64_t));
	memset(cliqueCounts, 0, KERNEL_INTERNAL_CONCURRENCY * sizeof(uint64_t));

	uint64_t* adjMatrix = generateAdjacencyMatrix(n, 0.5);

	max_file_t* maxfile = Bitstream_init();
	max_engine_t* engine = max_load(maxfile, "*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	//===========
	max_set_ticks(actions, "InputKernel", totalTickCount);
	max_set_uint64t(actions, "InputKernel", "loadTickCount", LOAD_TICK_COUNT);
	//===========

	const float startTimeBeforeInit = (float)clock()/CLOCKS_PER_SEC;

	//===========
	for (int i = 0; i < NUMBER_OF_COUNTER_KERNELS; ++i) {
		char counterKernelName[64];
		snprintf(counterKernelName, sizeof(counterKernelName), "GraphCliqueDFEKernel_%d", i);
		const int currentIdx = i * KERNEL_INTERNAL_CONCURRENCY;

		max_set_ticks(actions, counterKernelName, maxComputeTickCount);
		max_set_uint64t(actions, counterKernelName, "initialSubset0", partitions[currentIdx].initialSubset);
		max_set_uint64t(actions, counterKernelName, "initialSubset1", partitions[currentIdx + 1].initialSubset);
		max_set_uint64t(actions, counterKernelName, "initialSubset2", partitions[currentIdx + 2].initialSubset);
		max_set_uint64t(actions, counterKernelName, "initialSubset3", partitions[currentIdx + 3].initialSubset);
		max_set_uint64t(actions, counterKernelName, "limit0", partitions[currentIdx].limit);
		max_set_uint64t(actions, counterKernelName, "limit1", partitions[currentIdx + 1].limit);
		max_set_uint64t(actions, counterKernelName, "limit2", partitions[currentIdx + 2].limit);
		max_set_uint64t(actions, counterKernelName, "limit3", partitions[currentIdx + 3].limit);
	}
	//===========

	for (int i = 0; i < NUMBER_OF_COLLECTOR_KERNELS; ++i) {
		char collectorKernelName[64];
		snprintf(collectorKernelName, sizeof(collectorKernelName), "PartialCollectorKernel_%d", i);
		max_set_ticks(actions, collectorKernelName, maxComputeTickCount);
		max_set_uint64t(actions, collectorKernelName, "computeTickCount", maxComputeTickCount);
	}

	max_set_ticks(actions, "FinalCollectorKernel", KERNEL_INTERNAL_CONCURRENCY);
	max_set_uint64t(actions, "FinalCollectorKernel", "computeTickCount", KERNEL_INTERNAL_CONCURRENCY);

	//===========
	max_queue_input(actions, "adjMatrixRow", adjMatrix, LOAD_TICK_COUNT * sizeof(uint64_t));
	//===========

	max_queue_output(actions, "cliqueCount", cliqueCounts, KERNEL_INTERNAL_CONCURRENCY * sizeof(uint64_t));


	const float startTimeCalcOnly = (float)clock()/CLOCKS_PER_SEC;

	max_run(engine, actions);
	
	const float endTime = (float)clock()/CLOCKS_PER_SEC;

	printf("Start time before partition: %f\n", startTimeBeforePartition);
	printf("Start time before init: %f\n", startTimeBeforeInit);
	printf("Start time calc only: %f\n", startTimeCalcOnly);
	printf("End time: %f\n", endTime);
	printf("Elapsed time since partition: %f\n", (endTime - startTimeBeforePartition));
	printf("Elapsed time since init: %f\n", (endTime - startTimeBeforeInit));
	printf("Elapsed time since calc: %f\n", (endTime - startTimeCalcOnly));

	for (int i = 0; i < KERNEL_INTERNAL_CONCURRENCY; ++i)
		printf("cliqueCounts[%d] = %lu\n", i, (unsigned long) cliqueCounts[i]);

	max_actions_free(actions);

	free(cliqueCounts);
	free(partitions);
	free(adjMatrix);

	return 0;
}
