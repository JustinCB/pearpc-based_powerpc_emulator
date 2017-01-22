#ifndef HAVE_G1_H
#define HAVE_G1_H
#ifdef G1
#ifdef __cplusplus
extern "C" {
#endif
void power_opc_abs(void);
void power_opc_clcs(void);
void power_opc_doz(void);
void power_opc_dozi();
void power_opc_lscbx(void);
void power_opc_maskg(void);
void power_opc_maskir(void);
void power_opc_nabs(void);
void power_opc_rlmi();
uint32 make_mask(uint32 mstart, uint32 mstop);
uint32 use_mask (uint32 mask, uint32 value, uint32 start);
void power_opc_rrib(void);
void power_opc_sle(void);
void power_opc_div(void);
void power_opc_divs(void);
void power_opc_mul(void);
void power_opc_sleq(void);
void power_opc_sliq(void);
void power_opc_slliq(void);
void power_opc_sllq(void);
void power_opc_slq(void);
void power_opc_sraiq(void);
void power_opc_sraq(void);
void power_opc_sre(void);
void power_opc_srea(void);
void power_opc_sreq(void);
void power_opc_srliq_sriq(void);
void power_opc_srlq(void);
void power_opc_srq(void);
#ifdef __cplusplus
}
#endif
#endif
#endif