#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "stddef.h"

int main()
{
    // current of the memory use for the current process
    int memory_use = memsize();
    printf("memory use: %d bytes\n", memory_use);

    // Allocating 20KB bytes of memory
    int size_mem = 20000;
    //her we say to the comp dont worry we know this type
    void* ptr = malloc(size_mem);

    // check if there is memory
    if (ptr == NULL) {
        printf("There is no memory\n");
        exit(0,"");
    }
      int new_mem_size = memsize();
    printf("Memory use after allocation: %d bytes\n", new_mem_size);

    // Free the allocated memory
    free(ptr);
    
    // Memory usage after the release
    int released_mem_size = memsize();
    printf("Memory usage after release: %d bytes\n", released_mem_size);
    exit(0,"");
    return 0;
}
