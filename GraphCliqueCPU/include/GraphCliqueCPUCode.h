/*
 * GraphCliqueCPUCode.h
 *
 *  Created on: Feb 22, 2026
 *      Author: pallai
 */

#ifndef GRAPHCLIQUECPUCODE_H_
#define GRAPHCLIQUECPUCODE_H_

const int CONCURRENCY = 2;

typedef struct {
	uint64_t initialSubset;
	uint64_t limit;
	uint64_t count;
} GosperPartition;

uint64_t binomialCoefficient(int n, int k);

uint64_t unrank(uint64_t rank, int k, int n);

void gospersSplit(int k, int n, int numPartitions, GosperPartition* partitions);

#endif /* GRAPHCLIQUECPUCODE_H_ */
