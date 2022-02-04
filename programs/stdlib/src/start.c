#include "nn_os.h"

extern int main(int argc, char** argv);

void c_start()
{
    struct process_arguments arguments;
    nn_os_process_get_arguments(&arguments);

    int res = main(arguments.argc, arguments.argv);
    if (res == 0)
    {

    }
} 