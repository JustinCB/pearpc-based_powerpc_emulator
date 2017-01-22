#include "ppc_cpu.h"
#ifndef NEWMMU_H_INCLUDED
#define NEWMMU_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif
int FASTCALL ppc_effective_to_physical_c(uint32 addr, int flags, void ** result);
int FASTCALL ppc_read_physical_qword_c(void * addr, Vector_t * result);
int FASTCALL ppc_read_physical_dword_c(void * addr, uint64 * result);
int FASTCALL ppc_read_physical_word_c(void * addr, uint32 * result);
int FASTCALL ppc_read_physical_half_c(void * addr, uint16 * result);
int FASTCALL ppc_read_physical_byte_c(void * addr, uint8 * result);

int FASTCALL ppc_read_effective_code_c(uint32 addr, uint32 * result);
int FASTCALL ppc_read_effective_qword_c(uint32 addr, Vector_t * result);
int FASTCALL ppc_read_effective_dword_c(uint32 addr, uint64 * result);
int FASTCALL ppc_read_effective_word_c(uint32 addr, uint32 * result);
int FASTCALL ppc_read_effective_half_c(uint32 addr, uint16 * result);
int FASTCALL ppc_read_effective_byte_c(uint32 addr, uint8 * result);

int FASTCALL ppc_write_physical_qword(void * addr, Vector_t data);
int FASTCALL ppc_write_physical_dword(void * addr, uint64 data);
int FASTCALL ppc_write_physical_word(void * addr, uint32 data);
int FASTCALL ppc_write_physical_half(void * addr, uint16 data);
int FASTCALL ppc_write_physical_byte(void * addr, uint8 data);

int FASTCALL ppc_write_effective_qword(uint32 addr, Vector_t data);
int FASTCALL ppc_write_effective_dword(uint32 addr, uint64 data);
int FASTCALL ppc_write_effective_word(uint32 addr, uint32 data);
int FASTCALL ppc_write_effective_half(uint32 addr, uint16 data);
int FASTCALL ppc_write_effective_byte(uint32 addr, uint8 data);

int FASTCALL ppc_direct_effective_memory_handle_c(uint32 addr, byte **ptr);
int FASTCALL ppc_direct_effective_memory_handle_code_c(uint32 addr, byte **ptr);
#ifdef __cplusplus
}
#endif

#define ppc_read_effective_code(addr, result) ppc_read_effective_code_c(addr, &result)
#define ppc_read_effective_qword(addr, result) ppc_read_effective_qword_c(addr, &result)
#define ppc_read_effective_dword(addr, result) ppc_read_effective_dword_c(addr, &result)
#define ppc_read_effective_word(addr, result) ppc_read_effective_word_c(addr, &result)
#define ppc_read_effective_half(addr, result) ppc_read_effective_half_c(addr, &result)
#define ppc_read_effective_byte(addr, result) ppc_read_effective_byte_c(addr, &result)

#define ppc_direct_effective_memory_handle(addr, ptr) ppc_direct_effective_memory_handle_c(addr, &ptr)
#define ppc_direct_effective_memory_handle_code(addr, ptr) ppc_direct_effective_memory_handle_code_c(addr, &ptr)
#endif