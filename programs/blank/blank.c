#include "../stdlib/src/nn_os.h"
#include "../stdlib/src/stdlib.h"
#include "../stdlib/src/stdio.h"
#include "../stdlib/src/string.h"

int main(int argc, char** argv)
{
    printf("My age is %i\n", 19);

    print("Hello how are you!\n");

    print(itoa(8763));

    putchar('Z');

    void* ptr = malloc(512);
    
    free(ptr);

    char buf[1024];
    nn_os_terminal_readline(buf, sizeof(buf), true);

    print(buf);

    char words[] = "hello how are you";

    const char* token = strtok(words, " ");
    while(token)
    {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }

    while(1) 
    {

    }
    return 0;
} 