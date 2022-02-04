#include "shell.h"
#include "../../stdlib/src/stdlib.h"
#include "../../stdlib/src/stdio.h"
#include "../../stdlib/src/nn_os.h"

int main(int argc, char** argv)
{
    print("NN_OS v1.0.0\n");
    while(1) 
    {
        print("> ");
        char buf[1024];
        nn_os_terminal_readline(buf, sizeof(buf), true);
        print("\n");
    }
    return 0;
} 