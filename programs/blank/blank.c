#include "../stdlib/src/nn_os.h"
#include "../stdlib/src/stdlib.h"
#include "../stdlib/src/stdio.h"
#include "../stdlib/src/string.h"

int main(int argc, char** argv)
{
    struct process_arguments arguments;
    nn_os_process_get_arguments(&arguments);

    printf("%i %s\n", arguments.argc, arguments.argv[0]);

    while(1) 
    {

    }
    return 0;
} 