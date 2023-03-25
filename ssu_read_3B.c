#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    char character;
    int fd;
    int line_count=0;

    if((fd=open("ssu_test.txt",O_RDONLY))<0){
        fprintf(stderr, "open error for %s\n","ssu_test.txt");
        exit(1);
    }

    while(1){
        // read() 호출을 통해 개행 문자의 개수를 세어 파일 내용이 몇 줄인지 출력한다. 
        if(read(fd, &character, 1)>0){  // &character에 buffer가 들어간다.  // 1은 sizeof(n byte)
            if(character=='\n'){
                line_count++;
            }
        }
        else{
            break;
        }
    }

    printf("Total line: %d\n", line_count);
    exit(0);
}