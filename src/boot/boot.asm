ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start ; Get those GDT offsets
DATA_SEG equ gdt_data - gdt_start

jmp short start
nop

; FAT16 Header
OEMIdentifier           db 'NN_OS   '
BytesPerSector          dw 0x200
SectorsPerCluster       db 0x80
ReservedSectors         dw 200
FATCopies               db 0x02
RootDirEntries          dw 0x40
NumSectors              dw 0x00
MediaType               db 0xF8
SectorsPerFat           dw 0x100
SectorsPerTrack         dw 0x20
NumberOfHeads           dw 0x40
HiddenSectors           dd 0x00
SectorsBig              dd 0x773594

; Extended BPB (Dos 4.0)
DriveNumber             db 0x80
WinNTBit                db 0x00
Signature               db 0x29
VolumeID                dd 0xD105
VolumeIDString          db 'NN_OS BOOT '
SystemIDString          db 'FAT16   '


start:
    jmp 0:step2

step2:
    cli ; Clear interrupts cuz we are gonna change some segment registers
    mov ax, 0x00
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    sti ; Enables interrupts again

.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:load32

; GDT: Global Descriptor Table
gdt_start:
gdt_null: ; 64 bits of zeros (null descriptor)
    dd 0x0
    dd 0x0

; offset 0x8
gdt_code:       ; CS should point to this
    dw 0xffff   ; Segment limit for 0-15 bits
    dw 0        ; Base 0-15 bits
    db 0        ; Base 16-23 bits
    db 0x9a     ; Access byte (default)
    db 11001111b ; High and low 4 bit flags (default)
    db 0        ; Base 24 - 31 bits

; offset 0x10
gdt_data:       ; DS, SS, ES, FS, GS should point to this
    dw 0xffff   ; Segment limit for 0-15 bits
    dw 0        ; Base 0-15 bits
    db 0        ; Base 16-23 bits
    db 0x92     ; Access byte (default)
    db 11001111b ; High and low 4 bit flags (default)
    db 0        ; Base 24 - 31 bits

gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start-1    ; Size of the descriptor
    dd gdt_start
[BITS 32]
load32:
    mov eax, 1
    mov ecx, 100
    mov edi, 0x100000
    call ata_lba_read
    jmp CODE_SEG:0x0100000

ata_lba_read:
    mov ebx, eax ; Backup the LBA
    ; Sending the highest 8 bits of the lba to the hard disk controller
    shr eax, 24 ; We shift eax by 24 bits to right so only 32-24 = 8 highest bits remain.
    or eax, 0xE0 ; selecting master drive
    mov dx, 0x1F6
    out dx, al ; Sending highest 8 bits of eax to al

    ; Sending total sectors to read
    mov eax, ecx
    mov dx, 0x1F2
    out dx, al

    ; Sending more bits of LBA
    mov eax, ebx ; restoring LBA
    mov dx, 0x1F3
    out dx, al

    mov dx, 0x1F4
    mov eax, ebx ; restore LBA just to make sure
    shr eax, 8
    out dx, al
    ; Finished sending more bits of the LBA

    ; Sending upper 16 bits of the LBA
    mov dx, 0x1F5
    mov eax, ebx ; restore LBA
    shr eax, 16
    out dx, al

    mov dx, 0x1f7
    mov al, 0x20
    out dx, al

; Reading all sectors into memory
.next_sector:
    push ecx

; Checking if we need to read
.try_again:
    mov dx, 0x1f7
    in al, dx
    test al, 8
    jz .try_again

    ; We will read 256 words at a time
    mov ecx, 256
    mov dx, 0x1F0
    rep insw ; stores 256 words (512 bytes) in load32 edi location
    pop ecx
    loop .next_sector ; reads sectors and goes like 100, 99, ....0 and then stops
    ret

times 510-($ - $$) db 0
dw 0xAA55