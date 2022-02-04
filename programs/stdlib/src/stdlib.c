#include "stdlib.h"
#include "nn_os.h"

void* malloc(size_t size)
{
    return nn_os_malloc(size);
}

void free(void* ptr)
{
    nn_os_free(ptr);
} 