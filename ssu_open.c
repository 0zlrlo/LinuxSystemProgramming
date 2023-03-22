#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>  // 이 선언이 있어야지 open이 열린다.
int main(void){
    char *fname = "ssu_test.txt";
    int fd;  // 정수형 파일 디스크립터가 return된다
    if((fd = open(fname,O_RDONLY)) < 0){  //if문으로 예외처리
    // ssu_text.txt 파일을 open()을 통해 오픈한다.
    // O_RDONLY: 파일을 읽기 전용으로만 오픈하며, 이 플래그로 오픈한 파일에 쓰기를 시도하면 에러 발생한다.
        fprintf(stderr, "open error for %s\n", fname);
        exit(1);  //문제가 있으면 1을 반환
    }
    else
        printf("Success!\n Filename: %s\n Descriptor: %d\n", fname, fd);  
    /* 실행결과로 fd의 값이 3이 나오는데, 그 이유는 정수형으로 open할 때마다 하나씩 증가된 값으로 출력되는데 0, 1, 2는 내부적으로 OS 커널이 만들어 주기 때문에
    사용자가 파일을 열면 3으로 열리게 되는 것이다.*/ 
    exit(0);  // 문제가 없으면 0을 반환
}