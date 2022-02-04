#ifndef NN_OS_H
#define NN_OS_H

#include <stddef.h>
#include <stdbool.h>

void print(const char* filename);
int nn_os_getkey();
void* nn_os_malloc(size_t size);
void nn_os_free(void* ptr);
void nn_os_putchar(char c);
int nn_os_getkeyblock();
void nn_os_terminal_readline(char* out, int max, bool output_while_typing);
void nn_os_process_load_start(const char* filename);

#endif 