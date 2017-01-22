#include <stdio.h>
#include "ppc_cpu.h"
#include "PearPC_CPU.H"
void ppc_cpu_execute(void * stack, unsigned int stack_allocated, unsigned long code, void * realcode, unsigned int code_size)
{
	ppc_cpu_init_config();
	if(!(ppc_cpu_init())) {
		fprintf(stderr, "Couldn't initialize powerpc cpu");
	}
	gCPU.bp = stack;
	#ifdef G5
	gCPU.pgpr[2] = (uint64)EBP;
	#else
	gCPU.gpr[1] = (uint32)EBP;
	#endif
	gCPU.stack_size = (NATIVEINT)stack_allocated;
	gCPU.code_offset = (NATIVEINT)code;
	gCPU.realcode = realcode;
	gCPU.code_size = (NATIVEINT)code_size;
	ppc_cpu_runn();
}