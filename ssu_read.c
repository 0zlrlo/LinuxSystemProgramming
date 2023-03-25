#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"

int main(int argc, char* argv[]){
    struct ssu_employee record;
    int fd;
    int record_num;
    // argc는 프로그램 실행 시 입력한 실행 파일 옵션의 개수가 저장된다.
    // argv는 프로그램 실행 시 입력한 옵션의 가변적인 개수의 문자열들이 저장된다.

    // ssu_employee 구조체의 데이터들이 저장되어 있는 파일을 인자로 전달받는다.
    if(argc<2){
        fprintf(stderr, "Usage:%s file\n", argv[0]);
        exit(1);
    }
    // 입력 받은 파일을 읽기 모드로 열기
    if((fd==open(argv[1], O_RDONLY))<0){  // open() 호출을 통해 오픈하는 작업(예외처리)
        fprintf(stderr, "open error for %s\n", argv[1]);
    }

    while(1){
        printf("Enter record number: ");
        scanf("%d", &record_num);  // 레코드 번호 입력 받기
        if(record_num<0){  // 음수 레코드 번호 입력 시 종료
            break;
        }
        if(lseek(fd, (long)record_num* sizeof(record), 0)<0){  // 해당 레코드 위치로 lseek()를 호출하여 오프셋의 위치를 이동시킨다.
        // record_num번째 레코드에 접근
            fprintf(stderr,"lseek error\n");
            exit(1);
        }
        // record_num 번째 레코드의 시작부분에서부터 record 사이즈만큼 읽음
        // 이는 곧 record_num 번째 레코드를 읽어들여 record 변수에 저장함을 의미
        if(read(fd, (char*)&record, sizeof(record))>0){  // read()를 ssu_employee 구조체 크기만큼 호출하면 구조체 내용을 읽어와 이를 record 변수에 저장한다.
            printf("Employee: %s Salary: %d\n", record.name, record.salary);
        }
        else{
            printf("Record %d not found\n",record_num);
        }
    }
    close(fd);
    exit(0);

}