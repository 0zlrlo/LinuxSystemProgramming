#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define CREATE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)  // 유저 읽기, 쓰기, 그룹 읽기, 기타 사용자 읽기 권한
char buf1[] = "1234567890";
char buf2[] = "ABCDEFGHIJ";

int main(void){
    char *fname = "ssu_hole.txt";
    int fd;

    if((fd = creat(fname, CREATE_MODE)) < 0){  // hole 파일을 생성한다.
        fprintf(stderr, "creat error for %s\n", fname);
        exit(1);
    }
    if(write(fd, buf1, 12) != 12){  // 1234567890까지 채워지면 나머지는 null로 채워진다.
        fprintf(stderr, "buf1 write error\n");
        exit(1);
    }
    if(lseek(fd, 15000, SEEK_SET) < 0){  // 15000 바이트만큼 이동
    // 그리고 파일의 오프셋 위치를 파일의 처음으로 지정
    // 현재 파일보다 큰 seek position으로 lseek하면 널문자로 빈 공간을 채우는데 이를 hole이라고 한다.
        fprintf(stderr, "lseek error\n");
        exit(1);
    }
    // 맥은 lseek이전에 write를 해서 리눅스와 다르게 나온다. -> delayed write
    if(write(fd, buf2, 12) != 12){  // 15000 바이트만큼 떨어진 곳에 ABCDEFGHIJ\0\0 채워진다.
        fprintf(stderr, "buf2 write error\n");
        exit(1);
    }
    exit(0);
}

    