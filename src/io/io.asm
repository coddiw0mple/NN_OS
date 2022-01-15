section .asm

global insb
global insw
global outb
global outw

insb:
    push ebp        ; Create stack frame
    mov ebp, esp

    xor eax, eax    ; eax has returned value so we make it 0
    mov edx, [ebp + 8]
    in al, dx       ; al is part of eax register

    pop ebp
    ret

insw:
    push ebp        ; Create stack frame
    mov ebp, esp

    xor eax, eax    ; eax has returned value so we make it 0
    mov edx, [ebp + 8]
    in ax, dx       ; al is part of eax register

    pop ebp
    ret

outb:
    push ebp        ; Create stack frame
    mov ebp, esp

    mov eax, [ebp + 12]
    mov edx, [ebp + 8]
    out dx, al

    pop ebp
    ret

outw:
    push ebp        ; Create stack frame
    mov ebp, esp

    mov eax, [ebp + 12]
    mov edx, [ebp + 8]
    out dx, ax

    pop ebp
    ret