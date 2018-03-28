#include <stdlib.h>
#include <stdio.h>

int main(){
	pid_t pid;
	int i = 0;
	for(i = 0; i<10; i++)
	{
		pid = fork();
		if (pid>0){
			printf("%s\n","zombie spawned");
			sleep(2);
			exit(0);
		}
	}
	exit(0);
}