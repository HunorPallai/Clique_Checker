/**\file */
#ifndef SLIC_DECLARATIONS_Simulation_H
#define SLIC_DECLARATIONS_Simulation_H
#include "MaxSLiCInterface.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define Simulation_PCIE_ALIGNMENT (16)


/*----------------------------------------------------------------------------*/
/*---------------------------- Interface default -----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'default'.
 * 
 * \param [in] ticks_FinalCollectorKernel The number of ticks for which kernel "FinalCollectorKernel" will run.
 * \param [in] ticks_GraphCliqueDFEKernel_0 The number of ticks for which kernel "GraphCliqueDFEKernel_0" will run.
 * \param [in] ticks_GraphCliqueDFEKernel_1 The number of ticks for which kernel "GraphCliqueDFEKernel_1" will run.
 * \param [in] ticks_GraphCliqueDFEKernel_2 The number of ticks for which kernel "GraphCliqueDFEKernel_2" will run.
 * \param [in] ticks_GraphCliqueDFEKernel_3 The number of ticks for which kernel "GraphCliqueDFEKernel_3" will run.
 * \param [in] ticks_InputKernel The number of ticks for which kernel "InputKernel" will run.
 * \param [in] ticks_PartialCollectorKernel_0 The number of ticks for which kernel "PartialCollectorKernel_0" will run.
 * \param [in] ticks_PartialCollectorKernel_1 The number of ticks for which kernel "PartialCollectorKernel_1" will run.
 * \param [in] ticks_PartialCollectorKernel_2 The number of ticks for which kernel "PartialCollectorKernel_2" will run.
 * \param [in] ticks_PartialCollectorKernel_3 The number of ticks for which kernel "PartialCollectorKernel_3" will run.
 * \param [in] inscalar_FinalCollectorKernel_computeTickCount Input scalar parameter "FinalCollectorKernel.computeTickCount".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_initialSubset0 Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset0".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_initialSubset1 Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset1".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_initialSubset2 Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset2".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_initialSubset3 Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset3".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_limit0 Input scalar parameter "GraphCliqueDFEKernel_0.limit0".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_limit1 Input scalar parameter "GraphCliqueDFEKernel_0.limit1".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_limit2 Input scalar parameter "GraphCliqueDFEKernel_0.limit2".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_limit3 Input scalar parameter "GraphCliqueDFEKernel_0.limit3".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_initialSubset0 Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset0".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_initialSubset1 Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset1".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_initialSubset2 Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset2".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_initialSubset3 Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset3".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_limit0 Input scalar parameter "GraphCliqueDFEKernel_1.limit0".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_limit1 Input scalar parameter "GraphCliqueDFEKernel_1.limit1".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_limit2 Input scalar parameter "GraphCliqueDFEKernel_1.limit2".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_limit3 Input scalar parameter "GraphCliqueDFEKernel_1.limit3".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_initialSubset0 Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset0".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_initialSubset1 Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset1".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_initialSubset2 Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset2".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_initialSubset3 Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset3".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_limit0 Input scalar parameter "GraphCliqueDFEKernel_2.limit0".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_limit1 Input scalar parameter "GraphCliqueDFEKernel_2.limit1".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_limit2 Input scalar parameter "GraphCliqueDFEKernel_2.limit2".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_limit3 Input scalar parameter "GraphCliqueDFEKernel_2.limit3".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_initialSubset0 Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset0".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_initialSubset1 Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset1".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_initialSubset2 Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset2".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_initialSubset3 Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset3".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_limit0 Input scalar parameter "GraphCliqueDFEKernel_3.limit0".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_limit1 Input scalar parameter "GraphCliqueDFEKernel_3.limit1".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_limit2 Input scalar parameter "GraphCliqueDFEKernel_3.limit2".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_limit3 Input scalar parameter "GraphCliqueDFEKernel_3.limit3".
 * \param [in] inscalar_InputKernel_loadTickCount Input scalar parameter "InputKernel.loadTickCount".
 * \param [in] inscalar_PartialCollectorKernel_0_computeTickCount Input scalar parameter "PartialCollectorKernel_0.computeTickCount".
 * \param [in] inscalar_PartialCollectorKernel_1_computeTickCount Input scalar parameter "PartialCollectorKernel_1.computeTickCount".
 * \param [in] inscalar_PartialCollectorKernel_2_computeTickCount Input scalar parameter "PartialCollectorKernel_2.computeTickCount".
 * \param [in] inscalar_PartialCollectorKernel_3_computeTickCount Input scalar parameter "PartialCollectorKernel_3.computeTickCount".
 * \param [in] instream_adjMatrixRow Stream "adjMatrixRow".
 * \param [in] instream_size_adjMatrixRow The size of the stream instream_adjMatrixRow in bytes.
 * \param [out] outstream_cliqueCount Stream "cliqueCount".
 * \param [in] outstream_size_cliqueCount The size of the stream outstream_cliqueCount in bytes.
 */
void Simulation(
	uint64_t ticks_FinalCollectorKernel,
	uint64_t ticks_GraphCliqueDFEKernel_0,
	uint64_t ticks_GraphCliqueDFEKernel_1,
	uint64_t ticks_GraphCliqueDFEKernel_2,
	uint64_t ticks_GraphCliqueDFEKernel_3,
	uint64_t ticks_InputKernel,
	uint64_t ticks_PartialCollectorKernel_0,
	uint64_t ticks_PartialCollectorKernel_1,
	uint64_t ticks_PartialCollectorKernel_2,
	uint64_t ticks_PartialCollectorKernel_3,
	uint64_t inscalar_FinalCollectorKernel_computeTickCount,
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset0,
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset1,
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset2,
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset3,
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit0,
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit1,
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit2,
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit3,
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset0,
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset1,
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset2,
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset3,
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit0,
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit1,
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit2,
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit3,
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset0,
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset1,
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset2,
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset3,
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit0,
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit1,
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit2,
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit3,
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset0,
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset1,
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset2,
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset3,
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit0,
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit1,
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit2,
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit3,
	uint64_t inscalar_InputKernel_loadTickCount,
	uint64_t inscalar_PartialCollectorKernel_0_computeTickCount,
	uint64_t inscalar_PartialCollectorKernel_1_computeTickCount,
	uint64_t inscalar_PartialCollectorKernel_2_computeTickCount,
	uint64_t inscalar_PartialCollectorKernel_3_computeTickCount,
	const void *instream_adjMatrixRow,
	size_t instream_size_adjMatrixRow,
	void *outstream_cliqueCount,
	size_t outstream_size_cliqueCount);

/**
 * \brief Basic static non-blocking function for the interface 'default'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] ticks_FinalCollectorKernel The number of ticks for which kernel "FinalCollectorKernel" will run.
 * \param [in] ticks_GraphCliqueDFEKernel_0 The number of ticks for which kernel "GraphCliqueDFEKernel_0" will run.
 * \param [in] ticks_GraphCliqueDFEKernel_1 The number of ticks for which kernel "GraphCliqueDFEKernel_1" will run.
 * \param [in] ticks_GraphCliqueDFEKernel_2 The number of ticks for which kernel "GraphCliqueDFEKernel_2" will run.
 * \param [in] ticks_GraphCliqueDFEKernel_3 The number of ticks for which kernel "GraphCliqueDFEKernel_3" will run.
 * \param [in] ticks_InputKernel The number of ticks for which kernel "InputKernel" will run.
 * \param [in] ticks_PartialCollectorKernel_0 The number of ticks for which kernel "PartialCollectorKernel_0" will run.
 * \param [in] ticks_PartialCollectorKernel_1 The number of ticks for which kernel "PartialCollectorKernel_1" will run.
 * \param [in] ticks_PartialCollectorKernel_2 The number of ticks for which kernel "PartialCollectorKernel_2" will run.
 * \param [in] ticks_PartialCollectorKernel_3 The number of ticks for which kernel "PartialCollectorKernel_3" will run.
 * \param [in] inscalar_FinalCollectorKernel_computeTickCount Input scalar parameter "FinalCollectorKernel.computeTickCount".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_initialSubset0 Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset0".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_initialSubset1 Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset1".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_initialSubset2 Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset2".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_initialSubset3 Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset3".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_limit0 Input scalar parameter "GraphCliqueDFEKernel_0.limit0".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_limit1 Input scalar parameter "GraphCliqueDFEKernel_0.limit1".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_limit2 Input scalar parameter "GraphCliqueDFEKernel_0.limit2".
 * \param [in] inscalar_GraphCliqueDFEKernel_0_limit3 Input scalar parameter "GraphCliqueDFEKernel_0.limit3".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_initialSubset0 Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset0".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_initialSubset1 Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset1".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_initialSubset2 Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset2".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_initialSubset3 Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset3".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_limit0 Input scalar parameter "GraphCliqueDFEKernel_1.limit0".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_limit1 Input scalar parameter "GraphCliqueDFEKernel_1.limit1".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_limit2 Input scalar parameter "GraphCliqueDFEKernel_1.limit2".
 * \param [in] inscalar_GraphCliqueDFEKernel_1_limit3 Input scalar parameter "GraphCliqueDFEKernel_1.limit3".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_initialSubset0 Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset0".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_initialSubset1 Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset1".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_initialSubset2 Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset2".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_initialSubset3 Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset3".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_limit0 Input scalar parameter "GraphCliqueDFEKernel_2.limit0".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_limit1 Input scalar parameter "GraphCliqueDFEKernel_2.limit1".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_limit2 Input scalar parameter "GraphCliqueDFEKernel_2.limit2".
 * \param [in] inscalar_GraphCliqueDFEKernel_2_limit3 Input scalar parameter "GraphCliqueDFEKernel_2.limit3".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_initialSubset0 Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset0".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_initialSubset1 Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset1".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_initialSubset2 Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset2".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_initialSubset3 Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset3".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_limit0 Input scalar parameter "GraphCliqueDFEKernel_3.limit0".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_limit1 Input scalar parameter "GraphCliqueDFEKernel_3.limit1".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_limit2 Input scalar parameter "GraphCliqueDFEKernel_3.limit2".
 * \param [in] inscalar_GraphCliqueDFEKernel_3_limit3 Input scalar parameter "GraphCliqueDFEKernel_3.limit3".
 * \param [in] inscalar_InputKernel_loadTickCount Input scalar parameter "InputKernel.loadTickCount".
 * \param [in] inscalar_PartialCollectorKernel_0_computeTickCount Input scalar parameter "PartialCollectorKernel_0.computeTickCount".
 * \param [in] inscalar_PartialCollectorKernel_1_computeTickCount Input scalar parameter "PartialCollectorKernel_1.computeTickCount".
 * \param [in] inscalar_PartialCollectorKernel_2_computeTickCount Input scalar parameter "PartialCollectorKernel_2.computeTickCount".
 * \param [in] inscalar_PartialCollectorKernel_3_computeTickCount Input scalar parameter "PartialCollectorKernel_3.computeTickCount".
 * \param [in] instream_adjMatrixRow Stream "adjMatrixRow".
 * \param [in] instream_size_adjMatrixRow The size of the stream instream_adjMatrixRow in bytes.
 * \param [out] outstream_cliqueCount Stream "cliqueCount".
 * \param [in] outstream_size_cliqueCount The size of the stream outstream_cliqueCount in bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *Simulation_nonblock(
	uint64_t ticks_FinalCollectorKernel,
	uint64_t ticks_GraphCliqueDFEKernel_0,
	uint64_t ticks_GraphCliqueDFEKernel_1,
	uint64_t ticks_GraphCliqueDFEKernel_2,
	uint64_t ticks_GraphCliqueDFEKernel_3,
	uint64_t ticks_InputKernel,
	uint64_t ticks_PartialCollectorKernel_0,
	uint64_t ticks_PartialCollectorKernel_1,
	uint64_t ticks_PartialCollectorKernel_2,
	uint64_t ticks_PartialCollectorKernel_3,
	uint64_t inscalar_FinalCollectorKernel_computeTickCount,
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset0,
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset1,
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset2,
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset3,
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit0,
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit1,
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit2,
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit3,
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset0,
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset1,
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset2,
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset3,
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit0,
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit1,
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit2,
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit3,
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset0,
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset1,
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset2,
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset3,
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit0,
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit1,
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit2,
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit3,
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset0,
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset1,
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset2,
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset3,
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit0,
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit1,
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit2,
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit3,
	uint64_t inscalar_InputKernel_loadTickCount,
	uint64_t inscalar_PartialCollectorKernel_0_computeTickCount,
	uint64_t inscalar_PartialCollectorKernel_1_computeTickCount,
	uint64_t inscalar_PartialCollectorKernel_2_computeTickCount,
	uint64_t inscalar_PartialCollectorKernel_3_computeTickCount,
	const void *instream_adjMatrixRow,
	size_t instream_size_adjMatrixRow,
	void *outstream_cliqueCount,
	size_t outstream_size_cliqueCount);

/**
 * \brief Advanced static interface, structure for the engine interface 'default'
 * 
 */
typedef struct { 
	uint64_t ticks_FinalCollectorKernel; /**<  [in] The number of ticks for which kernel "FinalCollectorKernel" will run. */
	uint64_t ticks_GraphCliqueDFEKernel_0; /**<  [in] The number of ticks for which kernel "GraphCliqueDFEKernel_0" will run. */
	uint64_t ticks_GraphCliqueDFEKernel_1; /**<  [in] The number of ticks for which kernel "GraphCliqueDFEKernel_1" will run. */
	uint64_t ticks_GraphCliqueDFEKernel_2; /**<  [in] The number of ticks for which kernel "GraphCliqueDFEKernel_2" will run. */
	uint64_t ticks_GraphCliqueDFEKernel_3; /**<  [in] The number of ticks for which kernel "GraphCliqueDFEKernel_3" will run. */
	uint64_t ticks_InputKernel; /**<  [in] The number of ticks for which kernel "InputKernel" will run. */
	uint64_t ticks_PartialCollectorKernel_0; /**<  [in] The number of ticks for which kernel "PartialCollectorKernel_0" will run. */
	uint64_t ticks_PartialCollectorKernel_1; /**<  [in] The number of ticks for which kernel "PartialCollectorKernel_1" will run. */
	uint64_t ticks_PartialCollectorKernel_2; /**<  [in] The number of ticks for which kernel "PartialCollectorKernel_2" will run. */
	uint64_t ticks_PartialCollectorKernel_3; /**<  [in] The number of ticks for which kernel "PartialCollectorKernel_3" will run. */
	uint64_t inscalar_FinalCollectorKernel_computeTickCount; /**<  [in] Input scalar parameter "FinalCollectorKernel.computeTickCount". */
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset0; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset0". */
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset1; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset1". */
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset2; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset2". */
	uint64_t inscalar_GraphCliqueDFEKernel_0_initialSubset3; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_0.initialSubset3". */
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit0; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_0.limit0". */
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit1; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_0.limit1". */
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit2; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_0.limit2". */
	uint64_t inscalar_GraphCliqueDFEKernel_0_limit3; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_0.limit3". */
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset0; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset0". */
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset1; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset1". */
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset2; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset2". */
	uint64_t inscalar_GraphCliqueDFEKernel_1_initialSubset3; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_1.initialSubset3". */
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit0; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_1.limit0". */
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit1; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_1.limit1". */
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit2; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_1.limit2". */
	uint64_t inscalar_GraphCliqueDFEKernel_1_limit3; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_1.limit3". */
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset0; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset0". */
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset1; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset1". */
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset2; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset2". */
	uint64_t inscalar_GraphCliqueDFEKernel_2_initialSubset3; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_2.initialSubset3". */
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit0; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_2.limit0". */
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit1; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_2.limit1". */
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit2; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_2.limit2". */
	uint64_t inscalar_GraphCliqueDFEKernel_2_limit3; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_2.limit3". */
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset0; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset0". */
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset1; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset1". */
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset2; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset2". */
	uint64_t inscalar_GraphCliqueDFEKernel_3_initialSubset3; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_3.initialSubset3". */
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit0; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_3.limit0". */
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit1; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_3.limit1". */
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit2; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_3.limit2". */
	uint64_t inscalar_GraphCliqueDFEKernel_3_limit3; /**<  [in] Input scalar parameter "GraphCliqueDFEKernel_3.limit3". */
	uint64_t inscalar_InputKernel_loadTickCount; /**<  [in] Input scalar parameter "InputKernel.loadTickCount". */
	uint64_t inscalar_PartialCollectorKernel_0_computeTickCount; /**<  [in] Input scalar parameter "PartialCollectorKernel_0.computeTickCount". */
	uint64_t inscalar_PartialCollectorKernel_1_computeTickCount; /**<  [in] Input scalar parameter "PartialCollectorKernel_1.computeTickCount". */
	uint64_t inscalar_PartialCollectorKernel_2_computeTickCount; /**<  [in] Input scalar parameter "PartialCollectorKernel_2.computeTickCount". */
	uint64_t inscalar_PartialCollectorKernel_3_computeTickCount; /**<  [in] Input scalar parameter "PartialCollectorKernel_3.computeTickCount". */
	const void *instream_adjMatrixRow; /**<  [in] Stream "adjMatrixRow". */
	size_t instream_size_adjMatrixRow; /**<  [in] The size of the stream instream_adjMatrixRow in bytes. */
	void *outstream_cliqueCount; /**<  [out] Stream "cliqueCount". */
	size_t outstream_size_cliqueCount; /**<  [in] The size of the stream outstream_cliqueCount in bytes. */
} Simulation_actions_t;

/**
 * \brief Advanced static function for the interface 'default'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void Simulation_run(
	max_engine_t *engine,
	Simulation_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'default'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simulation_run_nonblock(
	max_engine_t *engine,
	Simulation_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'default'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void Simulation_run_group(max_group_t *group, Simulation_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simulation_run_group_nonblock(max_group_t *group, Simulation_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'default'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void Simulation_run_array(max_engarray_t *engarray, Simulation_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simulation_run_array_nonblock(max_engarray_t *engarray, Simulation_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* Simulation_convert(max_file_t *maxfile, Simulation_actions_t *interface_actions);

/**
 * \brief Initialise a maxfile.
 */
max_file_t* Simulation_init(void);

/* Error handling functions */
int Simulation_has_errors(void);
const char* Simulation_get_errors(void);
void Simulation_clear_errors(void);
/* Free statically allocated maxfile data */
void Simulation_free(void);
/* returns: -1 = error running command; 0 = no error reported */
int Simulation_simulator_start(void);
/* returns: -1 = error running command; 0 = no error reported */
int Simulation_simulator_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SLIC_DECLARATIONS_Simulation_H */

