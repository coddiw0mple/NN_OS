#include "../stdlib/src/nn_os.h"
#include "../stdlib/src/stdlib.h"

int main(int argc, char** argv)
{
    print("Hello how are you!\n");

    void* ptr = malloc(512);
    if (ptr)
    {

    }

    while(1) 
    {
        if (getkey() != 0)
        {
            print("key was pressed\n");
        }
    }
    return 0;
} 