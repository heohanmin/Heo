#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<wait.h>
int main() {
	  // 프로세스 번호 (Process ID; PID)가 저장될 변수 pid
	  pid_t pid;

	    // 자식 프로세스를 생성한다.
	    // 성공시 0, 실패시 -1, 부모 프로세스이면 양수 (프로세스 ID)를 반환한다.
	    pid = fork();

		  if (pid < 0) {
			      // pid 가 음수이면 에러가 난 것이다.

			      fprintf(stderr, "fork failed!");
				      return -1;

					    } else if (pid == 0) {
							    // pid 가 0 이면 자식 프로세스이다.
							    // 자식 프로세스가 해야 할 일을 선언한다.

							    printf("자식 프로세스 (# %i)\n", getpid());

								  } else {
									      // pid 가 양수이면 부모 프로세스이다.
									      // 부모 프로세스가 해야 할 일을 선언한다.

									      printf("부모 프로세스 (# %i)\n", getpid());

										      // 자식 프로세스들이 모두 종료될 때 까지 기다린다.
										      wait(NULL);

											    }
		    return 0;
}
