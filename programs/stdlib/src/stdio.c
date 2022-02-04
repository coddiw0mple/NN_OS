#include "stdio.h"
#include "nn_os.h"

int putchar(int c)
{
    nn_os_putchar((char)c);
    return 0;
} 