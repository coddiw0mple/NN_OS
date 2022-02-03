#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10
#define NN_OS_TOTAL_INTERRUPTS 0x200

#define NN_OS_HEAP_SIZE_BYTES 104857600 // 100 mb heap size
#define NN_OS_HEAP_BLOCK_SIZE 4096
#define NN_OS_HEAP_ADDRESS 0x01000000
#define NN_OS_HEAP_TABLE_ADDRESS 0x00007E00

#define NN_OS_SECTOR_SIZE 512

#define NN_OS_MAX_FILESYSTEMS 12
#define NN_OS_MAX_FILE_DESCRIPTORS 512

#define NN_OS_MAX_PATH 108

#define NN_OS_TOTAL_GDT_SEGMENTS 6

#define NN_OS_PROGRAM_VIRTUAL_ADDRESS 0x400000
#define NN_OS_USER_PROGRAM_STACK_SIZE 1024 * 16
#define NN_OS_PROGRAM_VIRTUAL_STACK_ADDRESS_START 0x3FF000
#define NN_OS_PROGRAM_VIRTUAL_STACK_ADDRESS_END NN_OS_PROGRAM_VIRTUAL_STACK_ADDRESS_START - NN_OS_USER_PROGRAM_STACK_SIZE

#define NN_OS_MAX_PROGRAM_ALLOCATIONS 1024
#define NN_OS_MAX_PROCESSES 12

#define USER_DATA_SEGMENT 0x23
#define USER_CODE_SEGMENT 0x1b

#define NN_OS_MAX_ISR80H_COMMANDS 1024

#define NN_OS_KEYBOARD_BUFFER_SIZE 1024

#endif