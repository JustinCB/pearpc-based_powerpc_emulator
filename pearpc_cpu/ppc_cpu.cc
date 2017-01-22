/*
 *	PearPC
 *	ppc_cpu.cc
 *
 *	Copyright (C) 2003, 2004 Sebastian Biallas (sb@biallas.net)
 *      Portions Copyright (C) 2004 Apple Computer, Inc.
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
#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include "systhread.h"
#include "sysendian.h"
#include "snprintf.h"
#include "tracers.h"
#include "cpu.h"
#include "debug.h"
#include "info.h"
#include "debugger.h"
#include "tracers.h"
#include "ppc_cpu.h"
#include "ppc_dec.h"
#include "ppc_fpu.h"
#include "ppc_exc.h"
#include "ppc_mmu.h"
#include "ppc_tools.h"
#include "PearPC_CPU.H"
extern "C" {
	PPC_CPU_State gCPU;
}
Debugger *gDebugger;

static bool gSinglestep = false;
bool activate = false;

sys_mutex exception_mutex;

void ppc_cpu_wakeup()
{
}
extern "C" {
	void ppc_cpu_runn(void)
	{
		ppc_cpu_run();
	}
}
void ppc_cpu_run()
{
	gDebugger = new Debugger();
	gDebugger->mAlwaysShowRegs = true;
	uint ops=0;
	gCPU.effective_code_page = 0xffffffff;
	while (true) {
		gCPU.npc = gCPU.pc+4;
		int i = ppc_read_effective_code_c(gCPU.pc, &gCPU.current_opc);
		/* previous line reads current opcode */
		ppc_exec_opc();
		ops++;
		gCPU.pc = gCPU.npc;
	}
}

void ppc_cpu_stop()
{
	/* don't do anything */
}

uint64	ppc_get_clock_frequency(int cpu)
{
	return PPC_CLOCK_FREQUENCY;
}

uint64	ppc_get_bus_frequency(int cpu)
{
	return PPC_BUS_FREQUENCY;
}

uint64	ppc_get_timebase_frequency(int cpu)
{
	return PPC_TIMEBASE_FREQUENCY;
}

uint32	ppc_cpu_get_gpr(int cpu, int i)
{
	return gCPU.gpr[i];
}

void	ppc_cpu_set_gpr(int cpu, int i, uint32 newvalue)
{
	gCPU.gpr[i] = newvalue;
}

void	ppc_cpu_set_msr(int cpu, uint32 newvalue)
{
	gCPU.msr = newvalue;
}

void	ppc_cpu_set_pc(int cpu, uint32 newvalue)
{
	gCPU.pc = newvalue;
}

uint32	ppc_cpu_get_pc(int cpu)
{
	return gCPU.pc;
}

uint32	ppc_cpu_get_pvr(int cpu)
{
	return gCPU.pvr;
}

#include "configparser.h"
extern "C" {
	bool ppc_cpu_init(void)
	{
		memset(&gCPU, 0, sizeof gCPU);
		gCPU.pvr = 0x000c0201;		
		ppc_dec_init();
		// initialize srs (mostly for prom)
		for (int i=0; i<16; i++) {
			gCPU.sr[i] = 0x2aa*i;
		}
		sys_create_mutex(&exception_mutex);
	
		return true;
	}

	void ppc_cpu_init_config(void)
	{
	}
}