#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    char *fname = "ssu_test.txt";
    int fd;
    if((fd = creat(fname,0666)) < 0){
        fprintf(stderr, "create error for %s\n", fname);
        exit(1);
    }
    else{
        close(fd);  //파일이 닫힘으로써 해당 디스크립터의 모든 입출력 시도는 실패하게 된다.
        fd = open(fname, O_RDWR);  // creat()로 생성한 파일을 open()을 통해 오픈
        // O_RDWR: 파일을 읽기와 쓰기 모두 가능하도록 오픈한다.
        printf("Succeeded!\n<%s> is new readalbe and writable\n", fname);
    }
    exit(0);
}