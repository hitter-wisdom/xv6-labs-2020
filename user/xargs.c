
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
    char buf[512];
    char *full_argv[MAXARG];
    int num;
    int len;
    if(argc < 2){
        fprintf(2, "argument loss!\n");
        exit(1);
    }
    if(argc + 1 > MAXARG){
        fprintf(2, "arguements overflow!\n");
        exit(1);
    }
    for(num=1 ; num < argc ; num++){
        full_argv[num-1] = argv[num];
    }

    full_argv[argc] = 0;

    while (1) {
        num = 0;
        while (1) {
            len = read(0, &buf[num], 1);
            if(len <= 0 || buf[num] == '\n') break;
            num++;
        }
        if(num == 0) break;
        buf[num] = 0;
        full_argv[argc-1]=buf;
        if(fork() == 0){
            exec(full_argv[0], full_argv);
            exit(0);
        } else {
            wait(0);
        }
    }
    exit(0);
}
