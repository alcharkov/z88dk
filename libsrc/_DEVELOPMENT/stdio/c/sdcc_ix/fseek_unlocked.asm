
; int fseek_unlocked(FILE *stream, long offset, int whence)

SECTION code_stdio

PUBLIC _fseek_unlocked

_fseek_unlocked:

   pop af
   exx
   pop bc
   exx
   pop hl
   pop de
   pop bc
   
   push bc
   push de
   push hl
   exx
   push bc
   push af
   
   push bc
   exx
   
   ex (sp),ix
   
   call asm_fseek_unlocked
   
   pop ix
   ret
   
   INCLUDE "stdio/z80/asm_fseek_unlocked.asm"
