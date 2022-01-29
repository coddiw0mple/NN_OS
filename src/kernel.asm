[BITS 32]

global _start
extern kernel_main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp
    ; Enabling A20 line
    in al, 0x92
    or al, 2
    out 0x92, al
    
    ; Remapping the master PIC (Programmable Interrupt Controller)
    mov al, 00010001b
    out 0x20, al    ; Telling master PIC

    mov al, 0x20    ; It's where master ISR（Interrupt Service Routing) should start 
    out 0x21, al

    mov al, 00000001b   ; Putting in x86 mode
    out 0x21, al
    ; Done remapping
    sti
    
    call kernel_main
    
    jmp $

times 512-($ - $$) db 0