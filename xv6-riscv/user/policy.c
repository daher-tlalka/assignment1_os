#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "stddef.h"

int main(int argc, char** argv)
{
    if(argc <=1){
        printf("ERROR\n");
        exit(-1,"");
        return -1;
    }
    char* z = argv[1];
    if(strlen(z) == 1 && set_policy((int)(z[0]-'0'))==0){
        printf("Success\n");
        exit(0,"");
        return 0;
    }
    printf("ERROR\n");
    exit(-1,"");
    return -1;
}