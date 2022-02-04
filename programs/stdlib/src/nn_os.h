#ifndef NN_OS_H
#define NN_OS_H

#include <stddef.h>

void print(const char* filename);
int getkey();
void* nn_os_malloc(size_t size);
void nn_os_free(void* ptr);
void nn_os_putchar(char c);

#endif 