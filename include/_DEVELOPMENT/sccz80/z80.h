
// automatically generated by m4 from headers in proto subdir


#ifndef _Z80_H
#define _Z80_H

#include <stdint.h>

extern void __LIB__ __FASTCALL__ im2_init(void *im2_table_address);


extern void __LIB__ *im2_install_isr(uint16_t vector,void *isr);
extern void __LIB__ __CALLEE__ *im2_install_isr_callee(uint16_t vector,void *isr);
#define im2_install_isr(a,b) im2_install_isr_callee(a,b)


extern void __LIB__ *im2_create_generic_isr(uint16_t num_callbacks,void *address);
extern void __LIB__ __CALLEE__ *im2_create_generic_isr_callee(uint16_t num_callbacks,void *address);
#define im2_create_generic_isr(a,b) im2_create_generic_isr_callee(a,b)


extern void __LIB__ *im2_create_generic_isr_8080(uint16_t num_callbacks,void *address);
extern void __LIB__ __CALLEE__ *im2_create_generic_isr_8080_callee(uint16_t num_callbacks,void *address);
#define im2_create_generic_isr_8080(a,b) im2_create_generic_isr_8080_callee(a,b)


extern void __LIB__ im2_append_generic_callback(uint16_t vector,void *callback);
extern void __LIB__ __CALLEE__ im2_append_generic_callback_callee(uint16_t vector,void *callback);
#define im2_append_generic_callback(a,b) im2_append_generic_callback_callee(a,b)


extern void __LIB__ im2_prepend_generic_callback(uint16_t vector,void *callback);
extern void __LIB__ __CALLEE__ im2_prepend_generic_callback_callee(uint16_t vector,void *callback);
#define im2_prepend_generic_callback(a,b) im2_prepend_generic_callback_callee(a,b)


extern int __LIB__ im2_remove_generic_callback(uint16_t vector,void *callback);
extern int __LIB__ __CALLEE__ im2_remove_generic_callback_callee(uint16_t vector,void *callback);
#define im2_remove_generic_callback(a,b) im2_remove_generic_callback_callee(a,b)



extern void __LIB__ __FASTCALL__ z80_delay_ms(uint16_t ms);


extern void __LIB__ __FASTCALL__ z80_delay_tstate(uint16_t tstates);


extern uint16_t __LIB__ z80_get_int_state(void);


extern void __LIB__ __FASTCALL__ z80_set_int_state(uint16_t state);



extern uint8_t __LIB__ __FASTCALL__ z80_inp(uint16_t port);


extern void __LIB__ *z80_inir(void *dst,uint16_t port);
extern void __LIB__ __CALLEE__ *z80_inir_callee(void *dst,uint16_t port);
#define z80_inir(a,b) z80_inir_callee(a,b)


extern void __LIB__ *z80_indr(void *dst,uint16_t port);
extern void __LIB__ __CALLEE__ *z80_indr_callee(void *dst,uint16_t port);
#define z80_indr(a,b) z80_indr_callee(a,b)


extern void __LIB__ z80_outp(uint16_t port,uint16_t data);
extern void __LIB__ __CALLEE__ z80_outp_callee(uint16_t port,uint16_t data);
#define z80_outp(a,b) z80_outp_callee(a,b)


extern void __LIB__ *z80_otir(void *src,uint16_t port);
extern void __LIB__ __CALLEE__ *z80_otir_callee(void *src,uint16_t port);
#define z80_otir(a,b) z80_otir_callee(a,b)


extern void __LIB__ *z80_otdr(void *src,uint16_t port);
extern void __LIB__ __CALLEE__ *z80_otdr_callee(void *src,uint16_t port);
#define z80_otdr(a,b) z80_otdr_callee(a,b)


#define z80_bpoke(a,b)  (*(unsigned char *)(a) = b)
#define z80_wpoke(a,b)  (*(unsigned int *)(a) = b)

#endif
