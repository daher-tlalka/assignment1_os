#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "stddef.h"

void toString(int n, char* str) {
    int i = 1;
    str[0] = n%10 + '0';
    n = n/10;
    while(n > 0){
        str[i] = n%10 + '0';
        n = n/10;
        i++;
    }
    str[i] = '\0'; 
    //reverse
    for (int j=0;j<i/2;j++) {
        char temp = str[j];
        str[j] = str[i-j-1];
        str[i-j-1] = temp;
    }
}
int main()
{
    int cfsPriority;
    int rtime;
    int stime;
    int rutime;
    int pid1;
    // int pid2,pid3,pid4,pid5,pid6,pid7,pid8,pid9,pid10;
    int cf = 0;
    for(int i=0;i<10;i++){
        pid1=fork();
        if(pid1 == 0){
            set_cfs_priority(cf);
            for(int i=1;i<=1000000;i++){
                if(i%100000==0){
                    sleep(1);
                }
            }
            sleep(3*i);
            get_cfs_stats(getpid(),&cfsPriority,&rtime,&stime,&rutime);
            char str[20];
            write(1,"Process Id: ",strlen("Process Id: "));
            toString(getpid(),str);
            write(1,str,strlen(str));
            write(1,"\t",strlen("\t"));
            write(1,"CFSPriority: ",strlen("CFSPriority: "));
            toString(cfsPriority,str);
            write(1,str,strlen(str));
            write(1,"\t",strlen("\t"));
            write(1,"Run Time: ",strlen("Runnable Time: "));
            toString(rtime,str);
            write(1,str,strlen(str));
            write(1,"\t",strlen("\t"));
            write(1,"Sleep Time: ",strlen("Sleep Time: "));
            toString(stime,str);
            write(1,str,strlen(str));
            write(1,"\t",strlen("\t"));
            write(1,"Runnable Time: ",strlen("Runnable Time: "));
            toString(rutime,str);
            write(1,str,strlen(str));
            write(1,"\n",strlen("\n"));
            break;
        }
        cf += 1;
        cf %= 3;
    }
    int status;
    for(int z = 0;z<10;z++){
        wait(&status,"");
    }
    exit(0,"");
    return 0;
}