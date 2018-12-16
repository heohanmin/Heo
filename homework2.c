#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#define FIFO_NAME "FIFO_FD"

int main(void)
{
	char *saveword[1000]; //중복단어 저장장소
	char buf[1000];//단어받는 크기
	int num, fd;
	int roop = 1; // 중복단어 배열
	int count=0;
	int len;
	char word[100];

	printf("후 공!\n");
	while(1) {
		fd = open(FIFO_NAME, O_RDONLY); // FIFO_NAME을 읽기 형식으로 연다.
		printf("파일 연동 성공!"); //프로세스1이랑  연동시, 출력
		while(fgets(buf,sizeof(buf),stdin),!feof(stdin)){ // 프로세스1에 입력했던 buf
			if((len = read(fd,buf,1000))==0) // read 읽는다. buf
				perror("read2 error");
			else
				printf("상대가  입력한 단어2 : %s\n",buf);
				break;
		}
		fd = open(FIFO_NAME, O_WRONLY); //FIFO_NAME을  쓰기형식으로 연다.
		printf("입력 2 : ");

		while(fgets(buf,sizeof(buf),stdin),!feof(stdin)){
			if((len = write(fd,buf,1000))==0)
				perror("write2 error");
			else{
				printf("내가 입력한 단어2 : %s\n",buf);
			}
			break;
		}
	}
	while(1);
	return 0;
}
