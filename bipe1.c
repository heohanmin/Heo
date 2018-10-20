/*파이프 사용*/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>

int main(void) {
	int pfd[2];
	char buf[30];

	/*파이프 생성*/
	if(pipe(pfd) == -1){
		perror("pipe error");
		exit(1);
	}

	printf("writing to the file descriptor #%d\n",pfd[1]);
	write(pfd[1],"pipel",5);

	printf("Reading from the file descriptor #%d\n",pfd[0]);
	read(pfd[0],buf,5);

	printf("%s\n",buf);

	return 0;
}
