[BITS 32]

global _start
extern c_start
extern nn_os_exit

section .asm

_start:
    call c_start
    call nn_os_exit

    ret 