#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(void){
    char buf[BUFFER_SIZE];
    char *fname = "ssu_test.txt";
    int count;
    int fd1, fd2;

    fd1 = open(fname, O_RDONLY, 0644); // 읽기 권한만
    fd2 = open(fname, O_RDONLY, 0644);  // 동일한 파일에 대해 두 번 open()를 호출 
    
    if(fd1<0||fd2<0){
        fprintf(stderr, "open error for %s\n", fname);
        exit(1);
    }

    // Linux System Programming! 읽어들여서 buf에 저장한다.
    // 이 때 널문자'\0' 는 buf에 없다.
    count = read(fd1, buf, 25);
    buf[count]= 0;  // 따라서 이 구문이 없으면 뒷 쪽의 쓰레기 값들이 %s 를 통해 출력된다. 
    printf("fd1's first printf: %s\n", buf);

    lseek(fd1, 1, SEEK_CUR);  // 줄바꿈을 읽지 않기 위해 seek position 1칸 이동
    count=read(fd1, buf, 24);  // Unix System Programming! 읽어서 buf에 저장
    buf[count]=0;
    printf("fd1's second printf: %s\n", buf);

    // 이제는 fd2 를 읽는다.
    // fd2 의 seek position 은 파일의 맨 앞에 있음
    count=read(fd2, buf, 25);
    buf[count]=0;
    printf("fd2's first printf: %s\n", buf);

    lseek(fd2, 1, SEEK_CUR);
    count=read(fd2, buf, 24);
    buf[count]=0;
    printf("fd2's second printf: %s\n", buf);

    exit(0);
}