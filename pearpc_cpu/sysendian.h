/*
 *	PearPC
 *	sysendian.h
 *
 *	Copyright (C) 1999-2004 Stefan Weyergraf
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License version 2 as
 *	published by the Free Software Foundation.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __SYSTEM_ARCH_SYSENDIAN_H__
#define __SYSTEM_ARCH_SYSENDIAN_H__

#include "types.h"
#include "config.h"
#if HOST_ENDIANESS == HOST_ENDIANESS_LE
#define ppc_dword_from_LE(dword) dword
#define ppc_word_from_LE(word) word
#define ppc_half_from_LE(half) half
#elif HOST_ENDIANESS == HOST_ENDIANESS_BE
#define ppc_dword_from_LE ppc_bswap_dword
#define ppc_word_from_LE ppc_bswap_word
#define ppc_half_from_LE ppc_bswap_half
#else
#error "What kind of a weird machine do you have? It's neither little- nor big-endian???   Were you messing around with config.h again?!?!"
#endif

#define ppc_dword_to_LE ppc_dword_from_LE
#define ppc_word_to_LE ppc_word_from_LE
#define ppc_half_to_LE ppc_half_from_LE

#endif
