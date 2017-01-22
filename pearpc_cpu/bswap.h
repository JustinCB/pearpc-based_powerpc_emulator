#ifndef BSWAP_H
#define BSWAP_H
#include "types.h"
#include "config.h"

#ifdef __x86_64__
#define INTEL_X86
#elif defined i386
#define INTEL_X86
#endif

#ifdef INTEL_X86
#define bswap(word) asm const("bswap %k0" : "=r" (word) : "0" (word) : );
static inline uint32 FASTCALL ppc_bswap_word(uint32 word)
{
	bswap(word);
	return word;
}
#else

#define ppc_bswap_word(data) (data>>24)|((data>>8)&0xff00)|((data<<8)&0xff0000)|(data<<24)

#endif

#define ppc_bswap_dword(data) (((uint64)ppc_bswap_word((uint32)data)) << 32) | (uint64)ppc_bswap_word((uint32)(data >> 32))

#define ppc_bswap_half(data) (data<<8)|(data>>8)


#if HOST_ENDIANESS == HOST_ENDIANESS_LE

#define ppc_half_to_BE ppc_bswap_half
#define ppc_word_to_BE ppc_bswap_word
#define ppc_dword_to_BE ppc_bswap_dword

#elif HOST_ENDIANESS == HOST_ENDIANESS_BE
#define  ppc_half_to_BE(half)  half
#define  ppc_word_to_BE(word)  word
#define ppc_dword_to_BE(dword) dword

#endif

#define ppc_half_from_BE  ppc_half_to_BE
#define ppc_word_from_BE  ppc_word_to_BE
#define ppc_dword_from_BE ppc_dword_to_BE
#endif