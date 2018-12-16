#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#define FIFO_NAME "FIFO_FD"

int main(void)
{
	int i = 0;
	char *saveword[1000]; // 중복단어 저장 장소
	char buf[1000]; // 단어 받는 크기
	int num, fd;
	int count=0; // 중복단어 배열 옾기기
	int len;
	int start=1; // 무한반복.
	if(mknod(FIFO_NAME, S_IFIFO | 0666, 0)== -1){
		perror("mknod error"); // 파일 생성 실패시 오류문
	}
	printf("선공!\n");
	while(start) {
		fd = open(FIFO_NAME, O_WRONLY); // FIFO_NAME을 쓰기 형식으로 연다.
		printf("==============================\n");
		printf("입력 :");
		while(fgets(buf,sizeof(buf),stdin),!feof(stdin)){ // fgets로 입력받아 buf에 동적할당하여 저장해준다.
			if((len = write(fd,buf,1000))==0) // 글자 길이를 확인하는건데 0이면 쓰기가 실패했다는 말.
				perror("write1 error");
			else{
				printf("내가 입력한 단어 : %s\n",buf);
				break; // break를 적어주어 무한반복을 나가준다.
			}
		}
		if(count == 0){
			saveword[count] = (char*)malloc(sizeof(buf)+1); // 중복단어 배열에 동적할당하여 저장해준다.
			strcpy(saveword[count],buf); // saveword에 buf 문자열을 복사시킨다.
			count++;
		}
		saveword[count] = (char*)malloc(sizeof(buf)+1);
		strcpy(saveword[count],buf);
		if(i==0)
		{
			printf(" ");
		}
		else
		{
		for(i=0;i<count;i++)
		{
			if(strcmp(saveword[i],buf)==0) // saveword 배열을 돌리면서 입력하였던 buf랑 비교하여 중복된 단어를 검사한다.
			{
				printf("중복된 단어.\n");
				count--;
			}
		}
		}
		count++;
		printf("저장된 값 : %s",saveword[i]);
		printf("==============================\n");
		fd = open(FIFO_NAME, O_RDONLY); // FIFO_NAME을 읽기 형식으로 연다.
		while(fgets(buf,sizeof(buf),stdin),!feof(stdin)){ // 프로세스2에서 저장된 buf를 열어준다.
			if((len = read(fd,buf,1000))==0) // 읽기를 하여 0이면 읽기 실패라고 출력.
				perror("read1 error");
			else{
				printf("==============================\n");
				printf("상대가 입력한 단어 : %s\n",buf);
				break;
			}
		}
		if(count==0){
			saveword[count] = (char*)malloc(sizeof(buf)+1); //단어를 배열에 저장해준다.
			strcpy(saveword[count],buf); // saveword에 buf를 복사한다.
			count++;
		}
		saveword[count] = (char*)malloc(sizeof(buf)+1);
		strcpy(saveword[count],buf);
		if(i==1)
		{
			printf(" ");
		}
		else
		{
		for(i=0;i<count;i++)
		{
			if(strcmp(saveword[i],buf)==0)
			{
				printf("중복된 단어.\n");
				count--;
			}
		}
		}
		count++;
		printf("저장된 값 : %s",buf);
		printf("==============================\n");
	}
	return 0;
}
