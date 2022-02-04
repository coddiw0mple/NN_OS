#include "../stdlib/src/nn_os.h"
#include "../stdlib/src/stdlib.h"
#include "../stdlib/src/stdio.h"
#include "../stdlib/src/string.h"

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
} 