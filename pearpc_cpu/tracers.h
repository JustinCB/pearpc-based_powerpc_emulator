/*
 *	PearPC
 *	tracers.h
 *
 *	Copyright (C) 2003 Sebastian Biallas (sb@biallas.net)
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

#ifndef __TRACERS_H__
#define __TRACERS_H__

#include "types.h"
#include "snprintf.h"


#define PPC_CPU_TRACE(msg...) ht_printf((char *)"[CPU/CPU] " msg)
#define PPC_ALU_TRACE(msg...) ht_printf((char *)"[CPU/ALU] " msg)
#define PPC_FPU_TRACE(msg...) ht_printf((char *)"[CPU/FPU] " msg)
#define PPC_DEC_TRACE(msg...) ht_printf((char *)"[CPU/DEC] " msg)
#define PPC_ESC_TRACE(msg...) ht_printf((char *)"[CPU/ESC] " msg)
//#define PPC_EXC_TRACE(msg...) ht_printf((char *)"[CPU/EXC] " msg)
#define PPC_MMU_TRACE(msg...) ht_printf((char *)"[CPU/MMU] " msg)
#define PPC_OPC_TRACE(msg...) ht_printf((char *)"[CPU/OPC] " msg)
//#define IO_PROM_TRACE(msg...) ht_printf((char *)"[IO/PROM] " msg)
//#define IO_PROM_FS_TRACE(msg...) ht_printf((char *)"[IO/PROM/FS] " msg)
//#define IO_3C90X_TRACE(msg...) ht_printf((char *)"[IO/3c90x] " msg)
//#define IO_RTL8139_TRACE(msg...) ht_printf((char *)"[IO/rtl8139] " msg)
//#define IO_GRAPHIC_TRACE(msg...) ht_printf((char *)"[IO/GCARD] " msg)
//#define IO_CUDA_TRACE(msg...) ht_printf((char *)"[IO/CUDA] " msg)
//#define IO_PIC_TRACE(msg...) ht_printf((char *)"[IO/PIC] " msg)
//#define IO_PCI_TRACE(msg...) ht_printf((char *)"[IO/PCI] " msg)
//#define IO_MACIO_TRACE(msg...) ht_printf((char *)"[IO/MACIO] " msg)
//#define IO_NVRAM_TRACE(msg...) ht_printf((char *)"[IO/NVRAM] " msg)
//#define IO_IDE_TRACE(msg...) ht_printf((char *)"[IO/IDE] " msg)
//#define IO_USB_TRACE(msg...) ht_printf((char *)"[IO/USB] " msg)
#define IO_SERIAL_TRACE(msg...) ht_printf((char *)"[IO/SERIAL] " msg)
#define IO_CORE_TRACE(msg...) ht_printf((char *)"[IO/Generic] " msg)

#define PPC_CPU_WARN(msg...) ht_printf((char *)"[CPU/CPU] <Warning> " msg)
#define PPC_ALU_WARN(msg...) ht_printf((char *)"[CPU/ALU] <Warning> " msg)
#define PPC_FPU_WARN(msg...) ht_printf((char *)"[CPU/FPU] <Warning> " msg)
#define PPC_DEC_WARN(msg...) ht_printf((char *)"[CPU/DEC] <Warning> " msg)
#define PPC_ESC_WARN(msg...) ht_printf((char *)"[CPU/ESC] <Warning> " msg)
#define PPC_EXC_WARN(msg...) ht_printf((char *)"[CPU/EXC] <Warning> " msg)
#define PPC_MMU_WARN(msg...) ht_printf((char *)"[CPU/MMU] <Warning> " msg)
#define PPC_OPC_WARN(msg...) ht_printf((char *)"[CPU/OPC] <Warning> " msg)
#define IO_PROM_WARN(msg...) ht_printf((char *)"[IO/PROM] <Warning> " msg)
#define IO_PROM_FS_WARN(msg...) ht_printf((char *)"[IO/PROM/FS] <Warning> " msg)
#define IO_3C90X_WARN(msg...) ht_printf((char *)"[IO/3c90x] <Warning> " msg)
#define IO_RTL8139_WARN(msg...) ht_printf((char *)"[IO/rtl8139] <Warning> " msg)
#define IO_GRAPHIC_WARN(msg...) ht_printf((char *)"[IO/GCARD] <Warning> " msg)
#define IO_CUDA_WARN(msg...) ht_printf((char *)"[IO/CUDA] <Warning> " msg)
#define IO_PIC_WARN(msg...) ht_printf((char *)"[IO/PIC] <Warning> " msg)
#define IO_PCI_WARN(msg...) ht_printf((char *)"[IO/PCI] <Warning> " msg)
#define IO_MACIO_WARN(msg...) ht_printf((char *)"[IO/MACIO] <Warning> " msg)
#define IO_NVRAM_WARN(msg...) ht_printf((char *)"[IO/NVRAM] <Warning> " msg)
#define IO_IDE_WARN(msg...) ht_printf((char *)"[IO/IDE] <Warning> " msg)
#define IO_USB_WARN(msg...) ht_printf((char *)"[IO/USB] <Warning> " msg)
#define IO_SERIAL_WARN(msg...) ht_printf((char *)"[IO/SERIAL] <Warning> " msg)
#define IO_CORE_WARN(msg...) ht_printf((char *)"[IO/Generic] <Warning> " msg)

#define PPC_CPU_ERR(msg...) {ht_printf((char *)"[CPU/CPU] <Error> " msg);exit(1); } 
#define PPC_ALU_ERR(msg...) {ht_printf((char *)"[CPU/ALU] <Error> " msg);exit(1); }
#define PPC_FPU_ERR(msg...) {ht_printf((char *)"[CPU/FPU] <Error> " msg);exit(1); }
#define PPC_DEC_ERR(msg...) {ht_printf((char *)"[CPU/DEC] <Error> " msg);exit(1); }
#define PPC_ESC_ERR(msg...) {ht_printf((char *)"[CPU/ESC] <Error> " msg);exit(1); }
#define PPC_EXC_ERR(msg...) {ht_printf((char *)"[CPU/EXC] <Error> " msg);exit(1); }
#define PPC_MMU_ERR(msg...) {ht_printf((char *)"[CPU/MMU] <Error> " msg);exit(1); }
#define PPC_OPC_ERR(msg...) {ht_printf((char *)"[CPU/OPC] <Error> " msg);exit(1); }
#define IO_PROM_ERR(msg...) {ht_printf((char *)"[IO/PROM] <Error> " msg);exit(1); }
#define IO_PROM_FS_ERR(msg...) {ht_printf((char *)"[IO/PROM/FS] <Error> " msg);exit(1); }
#define IO_3C90X_ERR(msg...) {ht_printf((char *)"[IO/3c90x] <Error> " msg);exit(1); }
#define IO_RTL8139_ERR(msg...) {ht_printf((char *)"[IO/rtl8139] <Error> " msg);exit(1); }
#define IO_GRAPHIC_ERR(msg...) {ht_printf((char *)"[IO/GCARD] <Error> " msg);exit(1); }
#define IO_CUDA_ERR(msg...) {ht_printf((char *)"[IO/CUDA] <Error> " msg);exit(1); }
#define IO_PIC_ERR(msg...) {ht_printf((char *)"[IO/PIC] <Error> " msg);exit(1); }
#define IO_PCI_ERR(msg...) {ht_printf((char *)"[IO/PCI] <Error> " msg);exit(1); }
#define IO_MACIO_ERR(msg...) {ht_printf((char *)"[IO/MACIO] <Error> " msg);exit(1); }
#define IO_NVRAM_ERR(msg...) {ht_printf((char *)"[IO/NVRAM] <Error> " msg);exit(1); }
#define IO_IDE_ERR(msg...) {ht_printf((char *)"[IO/IDE] <Error> " msg);exit(1); }
#define IO_USB_ERR(msg...) {ht_printf((char *)"[IO/IDE] <Error> " msg);exit(1); }
#define IO_SERIAL_ERR(msg...) {ht_printf((char *)"[IO/SERIAL] <Error> " msg);exit(1); }
#define IO_CORE_ERR(msg...) {ht_printf((char *)"[IO/Generic] <Error> " msg);exit(1); }

/*
 *
 */
#ifndef PPC_CPU_TRACE
#define PPC_CPU_TRACE(msg...)
#endif

#ifndef PPC_ALU_TRACE
#define PPC_ALU_TRACE(msg...)
#endif

#ifndef PPC_FPU_TRACE
#define PPC_FPU_TRACE(msg...)
#endif

#ifndef PPC_DEC_TRACE
#define PPC_DEC_TRACE(msg...)
#endif

#ifndef PPC_EXC_TRACE
#define PPC_EXC_TRACE(msg...)
#endif

#ifndef PPC_ESC_TRACE
#define PPC_ESC_TRACE(msg...)
#endif

#ifndef PPC_MMU_TRACE
#define PPC_MMU_TRACE(msg...)
#endif

#ifndef PPC_OPC_TRACE
#define PPC_OPC_TRACE(msg...)
#endif

#ifndef PPC_OPC_WARN
#define PPC_OPC_WARN(msg...)
#endif

#ifndef IO_PROM_TRACE
#define IO_PROM_TRACE(msg...)
#endif

#ifndef IO_PROM_FS_TRACE
#define IO_PROM_FS_TRACE(msg...)
#endif

#ifndef IO_GRAPHIC_TRACE
#define IO_GRAPHIC_TRACE(msg...)
#endif

#ifndef IO_CUDA_TRACE
#define IO_CUDA_TRACE(msg...)
#endif

#ifndef IO_PIC_TRACE
#define IO_PIC_TRACE(msg...)
#endif

#ifndef IO_PCI_TRACE
#define IO_PCI_TRACE(msg...)
#endif

#ifndef IO_MACIO_TRACE
#define IO_MACIO_TRACE(msg...)
#endif

#ifndef IO_ISA_TRACE
#define IO_ISA_TRACE(msg...)
#endif

#ifndef IO_IDE_TRACE
#define IO_IDE_TRACE(msg...)
#endif

#ifndef IO_CORE_TRACE
#define IO_CORE_TRACE(msg...)
#endif

#ifndef IO_NVRAM_TRACE
#define IO_NVRAM_TRACE(msg...)
#endif

#ifndef IO_USB_TRACE
#define IO_USB_TRACE(msg...)
#endif

#ifndef IO_SERIAL_TRACE
#define IO_SERIAL_TRACE(msg...)
#endif

#ifndef IO_3C90X_TRACE
#define IO_3C90X_TRACE(msg...)
#endif

#ifndef IO_RTL8139_TRACE
#define IO_RTL8139_TRACE(msg...)
#endif

#endif

