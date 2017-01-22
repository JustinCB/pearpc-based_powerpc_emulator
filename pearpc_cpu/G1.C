#ifdef G1
#include "ppc_cpu.h"
#include "ppc_mmu.h"
#include "types.h"
#include "G1.H"
#define OPC_UPDATE_CRO(opcode) (opcode & 1)
#define OPC_UPDATE_OV(opcode) (opcode & 0x00000800)
#define CLEAR_CRO gCPU.cr &= 0x0FFFFFFFF
#define CLEAR_OV gCPU.xer &= 0xBFFFFFFF
#define SET_OV gCPU.xer |= 0xC00000000
/* main = opc & 0xFC000000 */
#define MAKE_RD (gCPU.current_opc & 0x03E00000 >> 21)
#define MAKE_RA (gCPU.current_opc & 0x001F0000 >> 16)
#define MAKE_RB (gCPU.current_opc & 0x0000FC00 >> 10)
#define MAKE_IMMEDIATE (gCPU.current_opc & 0x0000FFFF)
#define	UPDATE_CRO(value) CLEAR_CRO; \
  (sint32)value < 0 ? gCPU.cr |= (8 << 28) : (value == 0 ? gCPU.cr |= (2 << 28) : gCPU.cr |= (4 << 28))
#ifdef __x86_64__
#define ___X86___
#elif defined i386
#define ___X86___
#endif
#ifdef ___X86___
#define rol(v, r) asm const("roll %k1, %k0" : "=r" (v) : "0" (v) "r" (r) :)
#define ror(v, r) asm const("rorl %k1, %k0" : "=r" (v) : "0" (v) "r" (r) :)
#else
#define rol(v, r) for(int i = 0; i < r; i ++) v = ((v << 1) | (v >> 31))
#define ror(v, r) for (int i = 0; i < r; i ++) v = ((v >> 1) | (v << 31))
#endif
void power_opc_abs(void)
{
	uint32 rD = MAKE_RD;
	uint32 rA = MAKE_RA;
	sint32 signedval = (sint32)gCPU.gpr[rA];
	if ((uint32)signedval == 0x80000000) {
		if (OPC_UPDATE_CRO(gCPU.current_opc) {
			CLEAR_CRO;
			gCPU.cr |= (1 << 28);
		}
		if (OPC_UPDATE_OV(gCPU.current_opc)) {
			SET_OV;
		}
		gCPU.gpr[rD] = 0x80000000;
	}
	else if (signedval > 0) {
		if (OPC_UPDATE_CRO(gCPU.current_opc)) {
			gCPU.cr &= 0x0FFFFFFF;
			gCPU.cr |= (4 << 28);
		}
		if (OPC_UPDATE_OV(gCPU.current_opc)) {
			CLEAR_OV;
		}
		gCPU.gpr[rD] = gCPU.gpr[rA];
	}
	else if (signedval == 0) {
		if (OPC_UPDATE_CRO(gCPU.current_opc)) {
			CLEAR_CRO;
			gCPU.cr |= (2 << 28);
		}
		if (OPC_UPDATE_OV(gCPU.current_opc)) {
			CLEAR_OV;
		}
		gCPU.gpr[rD] = 0;
	}
	else if (signedval < 0) {
		if (OPC_UPDATE_CRO(gCPU.current_opc)) {
			CLEAR_CRO;
			gCPU.cr |= (8 << 28);
		}
		if (OPC_UPDATE_OV(gCPU.current_opc)) {
			CLEAR_OV;
		}
		gCPU.gpr[rD] = ((~(gCPU.gpr[rA])) + 1);
	}
}
void power_opc_clcs(void)
{
	uint32 rD = MAKE_RD;
	uint32 rA = MAKE_RA;
	if (!(rA & 0x18)) {
		/* invalid: "undefined" */
		gCPU.gpr[rD] = 0xBADBAD00;
	}
	else if (rA & 16) {
		/* invalid: "undefined" */
		gCPU.gpr[rD] = 0x0BADBAD0;
	}
	else if ((rA & 0x1C) == 8) {
		/* invalid: "undefined" */
		gCPU.gpr[rD] = 0x00BADBAD;
	}
	else {
		/* valid: rD = 64 */
		gCPU.gpr[rD] = 64;
	}
}
void power_opc_doz(void)
{
	uint32 rD = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	if ((sint32)gCPU.gpr[rA] >= (sint32)gCPU.gpr[rB]) {
		if (OPC_UPDATE_CRO(gCPU.current_opc)) {
			CLEAR_CRO;
			gCPU.cr |= (2 << 28);
		}
		if (OPC_UPDATE_OV(gCPU.current_opc)) {
			if(gCPU.gpr[rA] == gCPU.gpr[rB]) {
				/* unsigned overflow *
				 * ((~x) + x + 1)    *
				 * ALWAYS overflows  *
				 * for ANY value of  *
				 * X. doz uses ~rA  *
				 * + rB + 1, rather  *
				 * than (signed)rA - *
				 * (signed) rB       */
				SET_OV;
			}
			else {
				CLEAR_OV;
			}
		}
		gCPU.gpr[rD] = 0;
	}
	else {
		if (OPC_UPDATE_CRO(gCPU.current_opc)) {
			CLEAR_CRO;
			gCPU.cr |= (4 << 28);
		}
		if (OPC_UPDATE_OV(gCPU.current_opc)) {
			CLEAR_OV;
		}
		gCPU.gpr[rD] = ((~gCPU.gpr[rA]) + gCPU.gpr[rB] + 1)
	}
}
void power_opc_dozi()
{
	uint32 rD = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 immediate = MAKE_IMMEDIATE;
	if ((sint32)gCPU.gpr[rA] >= (sint32)immediate) {
		gCPU.gpr[rD] = 0;
	}
	else {
		gCPU.gpr[rD] = ((~gCPU.gpr[rA]) + immediate + 1);
	}
}
#include "ppc_mmu.h"
#include "NEWMMU.H"
void power_opc_lscbx(void)
{
	bool match = false;
	uint32 rD = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 addr;
	uint32 cro = 0;
	if (rA == 0) {
		addr = rB;
	}	
	else {
		addr = rA + rB;
	}
	uint32 number = (gCPU.xer  & 0x0000007F);
	if (number == 0) {
		gCPU.gpr[rD] = 0xBADBAD0F;
		if (OPC_UPDATE_CRO(gCPU.current_opc)) {
			gCPU.cr |= (0xF << 28);
			/* or CR0 = Undefined */
		}
		return;
	}
	uint8 temp;
	int i = 0;
	int j = 4;
	while (i <= number) {
		if (!j) {
			j = 4;
			rD ++;
			if (rD >= 32) {
				rD = 0;
			}
			if ((rD == rA && (rA != 0)) {
				rD ++;
			}
			if (rD == rB) {
				rD ++;
			}
		}
		gCPU.gpr[rD] &= (~(0xFF << (j * 8)));
		ppc_read_effective_byte_c(addr, &temp);
		gCPU.gpr[rD] |= (temp << (j * 8));
		if (temp == (gCPU.xer & 0x00007F80)) {
			gCPU.xer &= 0xFFFFFF80;
			gCPU.xer |= i;
			match = true;
			break;
		}
		addr ++;
		i ++;
		j --;
	}
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		if (gCPU.xer & 0x80000000) {
			cro |= 1;
		}
		if (match) {
			cro |= 2;
		}
		gCPU.cr = (cro << 28);
	}
}
uint32 make_mask(uint32 mstart, uint32 mstop) 
{
	if (mstart < (mstop + 1)) {
		for (i = mstart; i < mstop; i ++) {
			gCPU.gpr[rA] |= (1 << (32 - i));
		}
	}
	else if (mstart == (mstop + 1)) {
		gCPU.gpr[rA] = 0xFFFFFFFF;
	}
	else {
		gCPU.gpr[rA] = 0xFFFFFFFF;
		for (i = (mstop + 1); i < (mstart - 1); i ++) {
			gCPU.gpr[rA] &= (~(1 << (32 - i)));
		}
	}
}
void power_opc_maskg(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 mstart = (rS & 0x0000001F);
	uint32 mstop =  (rB & 0x0000001F);
	int i;
	gCPU.gpr[rA] = make_mask(mstart, mstop);
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
uint32 use_mask(uint32 mask, uint32 value, uint32 start)
{
	uint32 ret = start;
	int i;
	for (i = 0; i < 32; i ++) {
		if (mask & (1 << i)) {
			ret &= (~(1 << i));
			ret |= (gCPU.gpr[rS] & (1 << i));
		}
	}
}
void power_opc_maskir(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	gCPU.gpr[rA] = use_mask(gCPU.gpr[rB], gCPU.gpr[rS], gCPU.gpr[rA]);
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_nabs(void)
{
	uint32 rD = MAKE_RD;
	uint32 rA = MAKE_RA;
	if (gCPU.gpr[rA] == 0x80000000) {
		gCPU.gpr[rD] = gCPU.gpr[rA];
	}
	else {
		power_opc_abs();
		gCPU.gpr[rD] = -(gCPU.gpr[rD]);
	}
	if(OPCODE_UPDATE_OV(gCPU.current_opc)) {
		CLEAR_OV;
	}
	if (OPCODE_UPDATE_CRO(gCPU.current_opc)) {
		CLEAR_CRO;
		if (gCPU.gpr[rD]) {
			gCPU.cr |= (8 << 28);
		}
		else {
			gCPU.cr |= (2 << 28);
		}
	}
}

void power_opc_rlmi()
{
	uint32 rB = MAKE_RB;
	uint32 rA = MAKE_RA;
	uint32 rS = MAKE_RD;
	uint32 mask_begin = ((gCPU.current_opc & 0x000007C0) >> 6);
	uint32 mask_end =   ((gCPU.current_opc & 0x0000003E) >> 1);
	uint32 tmp = gCPU.gpr[rS];
	uint32 toRotate = (gCPU.gpr[rB] & 0x0000001F);
	uint32 mask = make_mask(mask_begin, mask_end);
	#ifdef ___X86___
	;
	#else
	int i;
	for(i = 0; i < toRotate; i ++) {
		tmp = ((tmp << 1) | (tmp >> 31));
	}
	#endif
	gCPU.gpr[rA] = use_mask(mask, tmp, gCPU.gpr[rA]);
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_rrib(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 toShift = (gCPU.gpr[rB] & 0x0000001F);
	gCPU.gpr[rA] |= ((gCPU.gpr[rS] & 0x80000000) >> toShift);
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_div(void)
{
	uint32 rD = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 ov = 0;
	uint64 divizer = ((gCPU.gpr[rA] << 32)|(gCPU.mq));
	uint64 kwoshint = divizer / gCPU.gpr[rB];
	if (kwoshint & 0xFFFFFFFF00000000) {
		ov = 1;
	}
	if (((sint64)divizer == -2 * 1024 * 1024 * 1024 /* -2^31 */) && (sint32)gCPU.gpr[rB] == -1) {
		gCPU.gpr[rD] = ((~(2 * 1024 * 1024 * 1024) + 1); /* -2^31 */
		gCPU.mq = 0;
		ov = 1;
	}
	else {
		gCPU.gpr[rD] = (uint32)kwoshint;
		gCPU.mq = divizer % gCPU.gpr[rB];
	}
	if (OPC_UPDATE_OV(gCPU.current_opc)) {
		if (ov) {
			SET_OV;
		}
		else {
			CLEAR_OV;
		}
	}
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		if (ov) {
			CLEAR_CRO;
			gCPU.cr |= (1 << 28);
		}
		else { 
			UPDATE_CRO(gCPU.gpr[rD]);
		}
	}
}
void power_opc_divs(void)
{
	uint32 rD = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	gCPU.gpr[rD] = gCPU.gpr[rA] / gCPU.gpr[rB];
	gCPU.mq = gCPU.gpr[rA] % gCPU.gpr[rB];
	if (OPC_UPDATE_OV(gCPU.current_opc)) {
		CLEAR_OV;
	}
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rD]);
	}
}
void power_opc_mul(void)
{
	uint32 rD = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint64 result = (gCPU.gpr[rA] * gCPU.gpr[rB]);
	gCPU.gpr[rD] = (uint32)result;
	gCPU.mq = ((uint32)result >> 32);
	if (OPC_UPDATE_OV(gCPU.current_opc)) {
		CLEAR_OV;
	}
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rD]);
	}
}
void power_opc_sle(void)
{
	uint32 rB = MAKE_RB;
	uint32 rA = MAKE_RA;
	uint32 rS = MAKE_RD;
	uint32 tmp = gCPU.gpr[rS];
	uint32 toRotate = (gCPU.gpr[rB] & 0x0000001F);
	uint32 mask = 0;
	int i;
	for (i = 31; i > toRotate; i --) {
		mask |= (1 << i);
	}
	rol(tmp, toRotate);
	gCPU.mq = tmp;
	gCPU.gpr[rA] = (tmp & mask);
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_sleq(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 tmp = gCPU.gpr[rS];
	uint32 toRotate = (gCPU.gpr[rB] & 0x0000001F);
	uint32 mask = 0;
	int i;
	for (i = 31; i > toRotate; i --) {
		mask |= (1 << i);
	}
	rol(tmp, toRotate);
	gCPU.gpr[rA] = use_mask(mask, tmp, gCPU.mq);
	gCPU.mq = tmp;
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_sliq(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 SH = MAKE_RB;
	uint32 mask = 0;
	uint32 tmp = gCPU.gpr[rS];
	int i;
	for (i = 31; i > toRotate; i --) {
		mask |= (1 << i);
	}
	rol(tmp, SH);
	gCPU.mq = tmp;
	gCPU.gpr[rA] = (tmp & mask);
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_sllq(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 mask = 0;
	uint32 tmp = gCPU.gpr[rS];
	uint32 toRotate = (gCPU.gpr[rB] & 0x0000001F);
	int i;
	for (i = 31; i > toRotate; i --) {
		mask |= (1 << i);
	}
	rol(tmp, toRotate);
	gCPU.gpr[rA] = use_mask(mask, tmp, gCPU.mq);
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_slq(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 toRotate = (gCPU.gpr[rB] & 0x0000001F);
	uint32 tmp = gCPU.gpr[rS];
	int i;
	uint32 mask = 0;
	if (!(gCPU.gpr[rB] & 0x00000200)) {
		for (i = 31; i > toRotate; i--) {
			mask |= (1 << i);
		}
	}
	rol(tmp, toRotate);
	gCPU.mq = tmp;
	gCPU.gpr[rA] = (tmp & mask);
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_sraiq(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 SH = MAKE_RB;
	uint32 tmp = gCPU.gpr[rS];
	uint32 temp;
	uint32 mask = 0xFFFFFFFF;
	ror(tmp, SH);
	for (int i = 31; i > SH; i--) {
		mask &= (~(1 << i));
	}
	gCPU.mq = tmp;
	if (gCPU.gpr[rS] & 0x80000000) {
		gCPU.gpr[rA] = 0xFFFFFFFF;
	}
	else {
		gCPU.gpr[rA] = (tmp & mask);
	}
	temp = (tmp & (~(mask)));
	tmp |= temp;
	tmp &= gCPU.gpr[rS];
	if (tmp & 0x80000000) {
		gCPU.xer |= (1 << 29);
	}
	else {
		gCPU.xer &= (~(1 << 29));
	}
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_sraq(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 mask = 0xFFFFFFFF;
	uint32 tmp = gCPU.gpr[rS];
	uint32 temp;
	uint32 toRotate = (gCPU.gpr[rB] & 0x0000001F);
	ror(tmp, toRotate);
	if (gCPU.gpr[rB] & 0x00000020) {
		for (int i = 31; i > SH; i--) {
			mask &= (~(1 << i));
		}
	}
	else {
		mask = 0;
	}
	gCPU.mq = tmp;
	if (gCPU.gpr[rS] & 0x80000000) {
		gCPU.gpr[rA] = 0xFFFFFFFF;
	}
	else {
		gCPU.gpr[rA] = (tmp & mask);
	}
	temp = (tmp & (~(mask));
	tmp |= temp;
	tmp &= gCPU.gpr[rS];
	if (tmp & 0x80000000) {
		gCPU.xer |= (1 << 29);
	}
	else {
		gCPU.xer &= (~(1 << 29));
	}
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_sre(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 tmp = gCPU.gpr[rS];
	uint32 toRotate = (rB & 0x0000001F);
	uint32 mask = 0;
	ror(tmp, toRotate);
	gCPU.mq = tmp;
	for (int i = 31; i > toRotate; i--) {
		mask &= (~(1 << i));
	}
	gCPU.gpr[rA] = (tmp & mask);
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_srea(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 mask = 0xFFFFFFFF;
	uint32 tmp = gCPU.gpr[rS];
	uint32 toRotate = (gCPU.gpr[rB] & 0x0000001F);
	ror(tmp, toRotate);
	for (int i = 31; i > toRotate; i--) {
		mask &= (~(1 << i));
	}
	gCPU.mq = tmp;
	if (gCPU.gpr[rS] & 0x80000000) {
		gCPU.gpr[rA] = 0xFFFFFFFF;
	}
	else {
		gCPU.gpr[rA] = (tmp & mask);
	}
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_sreq(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 mask = 0xFFFFFFFF;
	uint32 tmp = gCPU.gpr[rS];
	uint32 toRotate = (gCPU.gpr[rB] & 0x0000001F);
	ror(tmp, toRotate);
	for (int i = 0; i > toRotate; i--) {
		mask &= (~(1 << i));
	}
	gCPU.gpr[rA] = use_mask(mask, tmp, gCPU.mq);
	gCPU.mq = tmp;
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_srliq_sriq(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 SH = MAKE_RB;
	uint32 mask = 0xFFFFFFFF;
	uint32 tmp = gCPU.gpr[rS];
	ror(tmp, SH);
	for (int i = 0; i > SH; i--) {
		mask &= (~(1 << i));
	}
	ror(tmp, SH);
	if ((gCPU.current_opc & 0x00000EFE >> 1) == 696){
		gCPU.gpr[rA] = (tmp & mask);
	}
	else {
		gCPU.gpr[rA] = use_mask(mask, tmp, gCPU.mq);
	}
	gCPU.mq = tmp;
	if(OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_srlq(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 mask;
	uint32 toRotate = (gCPU.gpr[rB] & 0x0000001F);
	uint32 tmp = gCPU.gpr[rA];
	ror(tmp, toRotate);
	if (gCPU.gpr[rB] & 0x00000020) {
		mask = 0;
		for (int i = 31; i > toRotate; i++) {
			mask |= (1 << i);
		}
		gCPU.gpr[rA] = use_mask(mask, tmp, gCPU.mq);
	}
	else {
		mask = 0xFFFFFFFF;
		for (int i = 31; i > toRotate; i++) {
			mask &= (~(1 << i));
		}
		gCPU.gpr[rA] = (gCPU.mq & mask);
	}
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
void power_opc_srq(void)
{
	uint32 rS = MAKE_RD;
	uint32 rA = MAKE_RA;
	uint32 rB = MAKE_RB;
	uint32 tmp = gCPU.gpr[rS];
	uint32 toRotate = (gCPU.gpr[rB] & 0x0000001F);
	uint32 mask = 0xFFFFFFFF;
	ror(tmp, toRotate);
	gCPU.mq = tmp;
	if (gCPU.gpr[rB] & 0x00000020) {
		mask = 0;
	}
	else {
		for (int i = 31; i > toRotate; i++) {
			mask &= (~(1 << i));
		}
	}
	gCPU.gpr[rA] = (tmp & mask);
	if (OPC_UPDATE_CRO(gCPU.current_opc)) {
		UPDATE_CRO(gCPU.gpr[rA]);
	}
}
#endif