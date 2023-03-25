#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    char c;
    int fd;

    if((fd=open("ssu_test.txt",O_RDONLY))<0){
        fprintf(stderr, "open error for %s\n", "ssu_test.txt");
        exit(1);
    }
    while(1){
        if(read(fd,&c,1)>0){  // ssu_test.txt에서 내용을 1글자씩 읽어 들인다.
            putchar(c);
        }
        else{
            break;
        }
    }
    exit(0);
}