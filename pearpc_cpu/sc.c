#include "ppc_cpu.h"
#include "ppc_mmu.h"
#include "bswap.h"
#include "NEWMMU.H"
#include <stdlib.h>
#define OP(instruct)       ((instruct & 0xFC000000) >> 26)
#define SRC(instruct)      ((instruct & 0x003F0000) >> 16)
#define DEST(instruct)     ((instruct & 0x03C00000) >> 20)
#define IMMEDIATE(instruct) (instruct & 0x0000FFFF)
void sc(void)
{
	int * args;
	args = get_arguments();
	#error "sc function for system calls is inimplemented"
}

int * get_arguments(void)
{
	NATIVEINT backtrack = gCPU.lr;
	int j = 0;
	uint32 ins;
	int i;
	int s = 0;
	int inret = 0;
	int intargs[8];
	int intargtmp;
	float floatargtmp;
	double doubleargtmp;
	int floatargs[13];
	int * stackargs = NULL;
	int * stackarglocs = NULL;
	int stackargsize = 0;
	int * ret;
	for (i = 0; i < 8; i ++) {
		intargs[i] = 0;
	}
	for (i = 0; i < 13; i ++) {
		floatargs[i] = 0;
	}
	i = 0;
	while (i <= 6) {
		ins = ppc_bswap_word(*(uint32 *) backtrack);
		if ((OP(ins)==14)||(OP(ins)==15)||(OP(ins)==20)||(OP(ins)==21)||((OP(ins)>=23)&&(OP(ins)<=25))||((OP(ins)>=32)&&(OP(ins)<=35))||((OP(ins)>=40)&&(OP(ins)<=43))||(OP(ins)==46)&&(DEST(ins)>= 3)&&(DEST(ins)<=10)) 
		{/* if instruction is load int */
			i = 0;
			intargs[(DEST(ins) - 3)] = 1;
		}
		else if ((OP(ins) == 48) || (OP(ins) == 49) && (DEST(ins) >= 1) && (DEST(ins) <= 13)) {
			i = 0;
			/* if instruction is load float */
			floatargs[(DEST(ins) - 1)] = 1;
		}
		else if ((OP(ins) == 50) || (OP(ins) == 51) && (DEST(ins) >= 1) && (DEST(ins) <= 13)) {
			i = 0;
			/* if instruction is load double */
			floatargs[(DEST(ins) - 1)] = 2;
		}
		else if (((OP(ins)>=36)&&(OP(ins)<=37))||(OP(ins)==47)&&(DEST(ins)==1)) {
			/* if instruction is store int on stack */
			i = 0;
			if (!stackargssize) {
				stackargs = (int *)malloc(sizeof(int));
				stackarglocs = (int *)malloc(sizeof(int));
				stackargsize = (int)(sizeof(int));
			}
			else {
				stackargs = (int *)realloc(stackargs, (stackargsize + (sizeof(int))));
				stackarglocs = (int *)realloc(stackarglocs, (stackargsize + (sizeof(int))));
				stackargsize += (int)(sizeof(int));
			}
			stackargs[((stackargsize / (int)(sizeof(int))) - 1)] = 1;
			stackarglocs[((stackargsize / (int)(sizeof(int))) - 1)] = (int)IMMEDIATE(instruct);
		}
		else if ((OP(ins) == 52) || (OP(ins) == 53) && (DEST(ins) == 1)) {
			i = 0;
			/* if instruction is store float on stack */
			if (!stackargsize) {
				stackargs = (int *)malloc(sizeof(int));
				stackarglocs = (int *)malloc(sizeof(int));
				stackargsize = (int)(sizeof(int));
			}
			else {
				stackargs = (int *)realloc(stackargs, (stackargsize + (sizeof(int))));
				stackarglocs = (int *)realloc(stackarglocs, (stackargsize + (sizeof(int))));
				stackargsize += (int)(sizeof(int));
			}
			stackargs[((stackargsize / (int)(sizeof(int))) - 1)] = 2;
			stackarglocs[((stackargsize / (int(sizeof(int))) - 1)] = (int)IMMEDIATE(instruct);
		}
		else if ((OP(ins) == 54) || (OP(ins) == 55) && (DEST(ins) == 1)) {
			i = 0;
			/* if instruction is store double on stack */
			if (!stackargsize) {
				stackargs = (int *)malloc(sizeof(int));
				stackarglocs = (int *)malloc(sizeof(int));
				stackargsize = (int)(sizeof(int));
			}
			else {
				stackargs = (int *)realloc(stackargs, (stackargsize + (sizeof(int))));
				stackarglocs = (int *)realloc(stackarglocs, (stackargsize + (sizeof(int))));
				stackargsize += (int)(sizeof(int));
			}
			stackargs[((stackargsize / (int)(sizeof(int))) - 1)] = 3;
			stackarglocs[((stackargsize / (int(sizeof(int))) - 1)] = (int)IMMEDIATE(instruct);
		}
		else {
			i ++;
		}
	}
	ret = (int *)malloc(sizeof(int));
	*ret = 0;
	if ((!(intargs[0])) && (!(floatargs[0]))) {
		return ret;
		/* ret[0] is number of arguments(set to zero above) */
	}
	/* else: */
	for(i = 0; i < 8; i++)
		if(intargs[i]) {
			*ret ++;
			ret = (int *)realloc(ret, (*ret * (sizeof(int))));
			ret[*ret] = gCPU.gpr[i + 3];
		}
		else if (floatargs[j] == 1) {
			*ret ++;
			ret = (int *)realloc(ret, (*ret * (sizeof(int))));
			ret[*ret] = (int)(gCPU.fpr[j + 1] & 0xFFFFFFFF);
			j ++;
			i ++;
		}
		else if (floatargs[j] == 2) {
			*ret += 2;
			ret = (int *)realloc(ret, (*ret * (sizeof(int))));
			ret[(*ret - 1)] = (int)(gCPU.fpr[j + 1] & 0xFFFFFFFF);
			ret[*ret] = (int)(gCPU.fpr[j + 1] >> 32);
			i +=2;
			j ++;
		}
		else if (!(intargs[i + 1])) {
			break;
		}
		else {
			fprintf(stderr, "bad arguments");
			exit(1);
		}
	}
	if (i == 8) {
		while(j < 13) {
			if (floatargs[j] == 1) {
				*ret ++;
				ret = (int *)realloc(ret, ((*ret * (sizeof(int))));
				ret[*ret] = (gCPU.fpr[j + 1] & 0xFFFFFFFF);
				j ++;
			}
			else if (floatargs[j] == 2) {
				*ret += 2;
				ret = (int *)realloc(ret, ((*ret * (sizeof(int))));
				ret[(*ret - 1)] = (int)(gCPU.fpr[j + 1] & 0xFFFFFFFF);
				ret[*ret] = (int)(gCPU.fpr[j + 1] >> 32);
				i +=2;
				j ++;
			} 
			else if ((stackargs[s] == 1) && ((s * (sizeof(int))) <= stackargsize)) {
				*ret ++;
				ret = (int *)realloc(ret, ((*ret * (sizeof(int))));
				inret = ppc_read_effective_word((gCPU.gpr[2] + stackarglocs[s]), (uint32)intargtmp);
				if (inret) {
					fprintf(stderr, "error reading integer stack argument");
					exit(1);
				}
				ret[*ret] = intargtmp;
				if ((s * (sizeof(int))) == stackargsize)) {
					break;
				}
				else {
					s ++;
				}
			}
			else {
				fprintf(stderr, "bad arguments");
				exit(1);
			}
		}
		while (1) { /* not really infinite */
			else if ((stackargs[s] == 2) && ((s * (sizeof(int))) <= stackargsize)) {
				*ret ++;
				ret = (int *)realloc(ret, ((*ret * (sizeof(int))) + sizeof(int)));
				inret = ppc_read_effective_word_c((gCPU.gpr[2] + stackarglocs[s]), (uint32 *)&floatargtmp);
				if (inret) {
					fprintf(stderr, "error reading floating point stack argument");
					exit(1);
				}
				ret[*ret] = *(int *)&floatargtmp;
				if ((s * (sizeof(int))) == stackargsize)) {
					break;
				}
				else {
					s ++;
				}
			}
			else if ((stackargs[s] == 2) && ((s * (sizeof(int))) <= stackargsize)) {
				*ret += 2;
				ret = (int *)realloc(ret, ((*ret * (sizeof(int))) + (sizeof(int) * 2)));
				inret = ppc_read_effective_dword_c((gCPU.gpr[2] + stackarglocs[s]), (uint64 *)&doubleargtmp);
				if (inret) {
					fprintf(stderr, "error reading floating point stack argument");
					exit(1);
				}
				ret[(*ret - 1)] = (int)(*(uint64 *)&doubleargtmp & 0xFFFFFFFF)
				ret[*ret] = (int)(*(uint64 *)&doubleargtmp >> 32);
				if ((s * (sizeof(int))) == stackargsize)) {
					break;
				}
				else {
					s ++;
				}
			}
		}
	}
	return ret;
}
			