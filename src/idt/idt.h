#ifndef IDT_H
#define IDT_H

#include <stdint.h>

void idt_init();
void enable_interrupts();
void disable_interrupts();

struct idt_desc
{
    uint16_t offset_1;  // Lower offset (0-15)
    uint16_t selector;  // Selector in our GDT (Gloabl descriptor table)
    uint8_t zero;       // Unused to set to 0
    uint8_t type_attr;  // Descriptor type and attributes
    uint16_t offset_2;  // Upper offset (16-31)
} __attribute__((packed));

struct idtr_desc
{
    uint16_t limit;     // Size of descriptor table - 1
    uint32_t base;      // Base address of the start of the IDT
}  __attribute__((packed));

#endif