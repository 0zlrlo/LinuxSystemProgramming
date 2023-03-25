#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define TABLE_SIZE 128
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    static struct {
        long offset;  // 데이터가 시작하는 위치
        int length;   // 데이터의 총 길이
    } table[TABLE_SIZE];

    char buf[BUFFER_SIZE];
    long offset;
    int entry;
    int i;
    int length;
    int fd;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        fprintf(stderr, "open error for %s\n", argv[1]);
        exit(1);
    }

    entry = 0;
    offset = 0;
    // 파일을 끝까지 읽음
    while ((length = read(fd, buf, BUFFER_SIZE)) > 0) {
    	// 매 글자 체크
        for (int i = 0; i < length; i++) {
            table[entry].length++;
            offset++;

			// 개행문자가 발견되면 table의 다음 entry에 offset을 저장한다.
            if (buf[i] == '\n')
                table[++entry].offset = offset;
        }
    }
    #ifdef DEBUG
    for (i = 0; i < entry; i++){
        printf("%d : %ld, %d\n", i + 1, table[i].offset, table[i].length);
    }
    #endif

    while (1) {
        printf("Enter line number : ");
        scanf("%d", &length);

        if (--length < 0){
            break;
        }
		// table[length].offset에는 length번째 줄이 파일의 몇 바이트 부분에서 시작되는지 저장되어 있으므로 해당 위치로 찾아간다.
        lseek(fd, table[length].offset, 0);

		// table[length].length 만큼 읽으면 length 번째 줄을 다 읽게됨
        if (read(fd, buf, table[length].length) <= 0) 
            continue;

        buf[table[length].length] = '\0';
        printf("%s", buf);
    }

    close(fd);
	exit(0);
}