
; int fileno_unlocked(FILE *stream)

SECTION code_stdio

PUBLIC _fileno_unlocked

_fileno_unlocked:

   pop af
   pop bc
   
   push bc
   push af
   
   push bc
   ex (sp),ix
   
   call asm_fileno_unlocked
   
   pop ix
   ret
   
   INCLUDE "stdio/z80/asm_fileno_unlocked.asm"
