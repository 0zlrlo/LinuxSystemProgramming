#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(void){
    char *fname = "ssu_test.txt";
    off_t fsize;  // off_t는 <sys/types.h>에 들어있으며 long형 정수를 의미한다.
    int fd;
    if((fd = open(fname, O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n", fname);
        exit(1);
    }
    // 파일의 끝에 내용을 추가한다.
    if((fsize = lseek(fd, 0, SEEK_END)) < 0){ // SEEK_END(파일의 끝)의 seek position은 파일 size와 같다.
        fprintf(stderr, "lseek error\n");
        exit(1);
    }
    printf("The size of <%s> is %ld bytes.\n", fname, fsize);  // ssu_test.txt 파일의 크기가 바이트 단위로 나온다.
    exit(0);
}