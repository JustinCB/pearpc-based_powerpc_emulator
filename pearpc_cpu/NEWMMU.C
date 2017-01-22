#include "ppc_cpu.h"
#include "ppc_mmu.h"
#include "PearPC_CPU.H"
#include "NEWMMU.H"
int FASTCALL ppc_effective_to_physical_c(uint32 addr, int flags, void ** result)
{
	if ((flags & PPC_MMU_CODE) && (addr > gCPU.code_offset) && ((addr - gCPU.code_offset) < gCPU.code_size)) {
		*result = ((char *)gCPU.realcode + (addr - gCPU.code_offset));
		return PPC_MMU_OK;
	}
	else if (flags & PPC_MMU_CODE) {
		return PPC_MMU_EXC;
	}
	else if ((addr < EBP) && ((EBP - addr) < gCPU.stack_size)) {
		/* stack translation */
		*result = ((char *)gCPU.bp + (EBP - addr));
	}
	else {
		*result = (void *)addr;
	}
	return PPC_MMU_OK;
}
int FASTCALL ppc_read_physical_qword_c(void * addr, Vector_t * result)
{
	result->d[0] = ppc_dword_from_BE(*(uint64 *)addr);
	result->d[1] = ppc_dword_from_BE(*(uint64 *)((char *)addr + 8));
	return PPC_MMU_OK;
}
int FASTCALL ppc_read_physical_dword_c(void * addr, uint64 * result)
{
	*result = ppc_dword_from_BE(*(uint64 *)addr);
	return PPC_MMU_OK;
}
int FASTCALL ppc_read_physical_word_c(void * addr, uint32 * result)
{
	*result = ppc_word_from_BE(*(uint32 *)addr);
	return PPC_MMU_OK;
}
int FASTCALL ppc_read_physical_half_c(void * addr, uint16 * result)
{
	*result = ppc_half_from_BE(*(uint16 *)addr);
	return PPC_MMU_OK;
}
int FASTCALL ppc_read_physical_byte_c(void * addr, uint8 * result)
{
	*result = *(uint8 *)addr;
	return PPC_MMU_OK;
}

int FASTCALL ppc_read_effective_code_c(uint32 addr, uint32 * result)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_READ | PPC_MMU_CODE, &p);
	if (!i) {
		return ppc_read_physical_word_c(p, result);
	}
	return i;
}
int FASTCALL ppc_read_effective_qword_c(uint32 addr, Vector_t * result)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_READ, &p);
	if (!i) {
		return ppc_read_physical_qword_c(p, result);
	}
	return i;
}
int FASTCALL ppc_read_effective_dword_c(uint32 addr, uint64 * result)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_READ, &p);
	if (!i) {
		return ppc_read_physical_dword_c(p, result);
	}
	return i;
}
int FASTCALL ppc_read_effective_word_c(uint32 addr, uint32 * result)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_READ, &p);
	if (!i) {
		return ppc_read_physical_word_c(p, result);
	}
	return i;
}
int FASTCALL ppc_read_effective_half_c(uint32 addr, uint16 * result)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_READ, &p);
	if (!i) {
		return ppc_read_physical_half_c(p, result);
	}
	return i;
}
int FASTCALL ppc_read_effective_byte_c(uint32 addr, uint8 * result)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_READ, &p);
	if (!i) {
		*result = *(uint8 *)p;
	}
	return i;
}

int FASTCALL ppc_write_physical_qword(void * addr, Vector_t data)
{
	*(uint64 *)addr = ppc_dword_to_BE(data.d[0]);
	*(uint64 *)((char *)addr + 8) = ppc_dword_to_BE(data.d[1]);
	return PPC_MMU_OK;
}
int FASTCALL ppc_write_physical_dword(void * addr, uint64 data)
{
	*(uint64 *)addr = ppc_dword_to_BE(data);
	return PPC_MMU_OK;
}
int FASTCALL ppc_write_physical_word(void * addr, uint32 data)
{
	*(uint32 *)addr = ppc_word_to_BE(data);
	return PPC_MMU_OK;
}
int FASTCALL ppc_write_physical_half(void * addr, uint16 data)
{
	*(uint16 *)addr = ppc_half_to_BE(data);
	return PPC_MMU_OK;
}
int FASTCALL ppc_write_physical_byte(void * addr, uint8 data)
{
	*(uint8 *)addr = data;
	return PPC_MMU_OK;
}

int FASTCALL ppc_write_effective_qword(uint32 addr, Vector_t data)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_WRITE, &p);
	if (!i) {
		return ppc_write_physical_qword(p, data);
	}
	return i;
}
int FASTCALL ppc_write_effective_dword(uint32 addr, uint64 data)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_WRITE, &p);
	if (!i) {
		return ppc_write_physical_dword(p, data);
	}
	return i;
}
int FASTCALL ppc_write_effective_word(uint32 addr, uint64 data)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_WRITE, &p);
	if (!i) {
		return ppc_write_physical_word(p, data);
	}
	return i;
}
int FASTCALL ppc_write_effective_half(uint32 addr, uint16 data)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_WRITE, &p);
	if (!i) {
		return ppc_write_physical_half(p, data);
	}
	return i;
}
int FASTCALL ppc_write_effective_byte(uint32 addr, uint8 data)
{
	void * p;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_WRITE, &p);
	if (!i) {
		*(uint8 *)p = data;
		return PPC_MMU_OK;
	}
	return i;
}	

int FASTCALL ppc_direct_effective_memory_handle_c(uint32 addr, byte**ptr)
{
	void * ea;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_READ, &ea);
	if (!i) {
		*ptr = (byte *)ea;
	}
	return i;
}

int FASTCALL ppc_direct_effective_memory_handle_code_c(uint32 addr, byte ** ptr)
{
	void * ea;
	int i = ppc_effective_to_physical_c(addr, PPC_MMU_READ | PPC_MMU_CODE, &ea);
	if (!i) {
		*ptr = (byte *)ea;
	}
	return i;
}