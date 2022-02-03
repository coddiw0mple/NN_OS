#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "memory/memory.h"
#include "disk/disk.h"
#include "string/string.h"
#include "fs/pparser.h"
#include "disk/streamer.h"
#include "fs/file.h"
#include "gdt/gdt.h"
#include "task/tss.h"
#include "task/task.h"
#include "task/process.h"
#include "isr80h/isr80h.h"
#include "keyboard/keyboard.h"
#include "config.h"
#include "status.h"

uint16_t* video_mem = 0;
uint16_t terminal_y = 0;
uint16_t terminal_x = 0;

uint16_t terminal_make_char(char c, char colour) // c is character, colour is ascii colour code
{
    return (colour << 8) | c; // Forms 16-bit unsigned short.
}

void terminal_put_char(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_write_char(char c, char colour)
{
    if (c == '\n') {
        terminal_x = 0;
        terminal_y += 1;
        return;
    }

    terminal_put_char(terminal_x, terminal_y, c, colour);
    terminal_x += 1;

    if (terminal_x >= VGA_WIDTH) {
        terminal_x = 0;
        terminal_y += 1;
    }
}

void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000);
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++) {
            terminal_put_char(x, y, ' ', 0);
        }
    }
}

void print(const char* str) 
{
    size_t len = strlen(str);

    for (int i = 0; i < len; i++) {
        terminal_write_char(str[i], 2);
    }
}

static struct paging_4gb_chunk* kernel_chunk = 0;

void panic(const char* msg)
{
    print(msg);
    while(1) {}
}

void kernel_page()
{
    kernel_registers();
    paging_switch(kernel_chunk);
}

struct tss tss;
struct gdt gdt_real[NN_OS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[NN_OS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},                // NULL Segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a},           // Kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92},            // Kernel data segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},              // User code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},             // User data segment
    {.base = (uint32_t)&tss, .limit=sizeof(tss), .type = 0xE9}      // TSS Segment
};

void pic_timer_callback(struct interrupt_frame* frame)
{
    print("Timer activated\n");
}

void kernel_main()
{
    terminal_initialize();

    memset(gdt_real, 0x00, sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real, gdt_structured, NN_OS_TOTAL_GDT_SEGMENTS);

    // Load the gdt
    gdt_load(gdt_real, sizeof(gdt_real));

    // Initializing our heap
    kheap_init();

    // Initialize filesystems
    fs_init();

    // Search and initialize the disks
    disk_search_and_init();

    // Initializing the global interrupt descriptor table
    idt_init();

    // Setup the TSS
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000;
    tss.ss0 = KERNEL_DATA_SELECTOR;

    // Load the TSS
    tss_load(0x28);

    // Setting up paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    
    // Switching to kernel paging chunk
    paging_switch(kernel_chunk);

    // Finally enabling paging
    enable_paging();

    // Register the kernel commands
    isr80h_register_commands();

    // Initialize all the system keyboards
    keyboard_init();

    idt_register_interrupt_callback(0x20, pic_timer_callback);

    struct process* process = 0;
    int res = process_load("0:/blank.bin", &process);
    if (res != NN_OS_ALL_OK)
    {
        panic("Failed to load blank.bin\n");
    } else {
        print("\nLoaded process successfully\n");
    }

    task_run_first_ever_task();

    while(1) {}

}