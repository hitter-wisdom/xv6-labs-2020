#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 0){
    printf("Usage: pingpong\n");
  }
  int p1[2];      //父进程写，子进程读
  int p2[2];      //父进程读，子进程写
  //pipe[1]为写端，pipe[0]为读端
  pipe(p1);
  pipe(p2);
  if(fork() == 0){
    char son_out[2];
        close(p1[1]);
        close(p2[0]);
        read(p1[0],son_out,1);
        close(p1[0]);
        printf("%d: received ping\n",getpid());
        write(p2[1],"s",2);
        close(p2[1]);
  }else{
        //父进程
        char fa_out[2];
        close(p1[0]);
        close(p2[1]);
        write(p1[1],"y",2);
        close(p1[1]);
        read(p2[0],fa_out,1);
        printf("%d: received pong\n",getpid());
        close(p2[0]);
  }
  exit(0);
}