#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

void prime(int p[2]){
    int num_noprime;        //上轮未drop的，无法确定的数
    int num_isprime;        //当前用于判断的以确定的质数，先输出
    int p1[2];
    close(p[1]);
    int flag1 = read(p[0],&num_isprime,4);
    if(flag1 == 0){
        close(p[0]);
        exit(1);
    }
    printf("prime %d\n",num_isprime);
    pipe(p1);
    int res = fork();
    if(res == 0){
        close(p[0]);
        prime(p1);
    }
    if(res != 0){
        close(p1[0]);
        while (1)
        {
            if(read(p[0],&num_noprime,4) == 0) break;
            if(num_noprime % num_isprime != 0){
                write(p1[1],&num_noprime,4);        //再次将目前无法确定的数传给子进程
            }
        }
        close(p[0]);
        close(p1[1]);
        wait(0);
    }
    exit(0);
}
int main(int agrc, char* argv[]){
    if(agrc != 1){
        printf("Usage: prime\n");
        exit(-1);
    }
    int num;
    int p[2];
    pipe(p);
    int res = fork();
    if(res == 0)    prime(p);
    if(res != 0){
        for(num=2;num<=35;num++)
        {
            write(p[1],&num,4);
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}