#include "ppc_cpu.h"
#ifndef PEARPC_CPU_H
#define PEARPC_CPU_H
#ifdef _cplusplus
extern "C" {
#endif
void ppc_cpu_execute(void * stack, unsigned int stack_allocated, unsigned long code, void * realcode, unsigned int code_size);
#ifdef _cplusplus
}
#endif
#ifdef G5
typedef uint64 NATIVEINT;
#else
typedef uint32 NATIVEINT;
#endif
#ifdef ABI64
#define EBP 0xFFFFFFFFFFFF0000
#define MAX_HEAP 0x000000FFFFFFFF
#else
#define EBP 0xFFFF0000
#define MAX_HEAP 0x3FFFFFFF
#endif
#endif