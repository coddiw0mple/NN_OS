#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"

uint16_t* video_mem = 0;
uint16_t terminal_y = 0;
uint16_t terminal_x = 0;

uint16_t terminal_make_char(char c, char colour) // c is character, colour is ascii colour code
{
    return (colour << 8) | c; // Forms 16-bit unsigned short.
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while(str[len]) // C puts null terminator at end of strings so this becomes false as soon as we hit the end
    {
        len++;
    }

    return len;
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

void kernel_main()
{
    terminal_initialize();
    
    print("Hello, World!\nThis is my first OS :)");

    // Initializing our heap
    kheap_init();

    // Initializing the global interrupt descriptor table
    idt_init();

    // Setting up paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    
    // Switching to kernel paging chunk
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));

    // Finally enabling paging
    enable_paging();

    char buf[512];
    disk_read_sector(0, 1, buf);

    // Enabling global system interrupts
    enable_interrupts();
}