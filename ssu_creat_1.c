#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    char *fname = "ssu_test.txt";
    int fd;
    if((fd = creat(fname, 0666)) < 0){  //0666: rwrwrw를 의미, int타입의 mode
        fprintf(stderr, "creat error for %s\n", fname);
        exit(1);
    }
    else{
        printf("Success!\n Filename: %s\n Descriptor: %d\n", fname, fd);
        close(fd);
    }
    exit(0);
}