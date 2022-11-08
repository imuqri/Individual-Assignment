#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	
	float currentSaving1;
	float currentSaving2;
	float fd1[2];
	
	
	pipe(fd1);
	pid_t pid = fork();
	
	if(pid > 0) {
		printf("Enter your current ASB saving : ");
		scanf("%f", &currentSaving1);
		close(fd1[0]);
		write(fd1[1], &currentSaving1, sizeof(currentSaving1);
	}
	
	else if(pid == 0) {
		wait(NULL);
		close(fd1[1]);
		read(fd1[0], &currentSaving2, sizeof(currentSaving1);
		close(fd1[0]);
		print("your current saving is : %f \n", currentSaving2);
		print("divident you will get this year is (4.5%) : %lf \n", currentSaving2*0.45);
	}
	//printf( "Your current ASB saving is: %f", currentSaving);
	
	return 0;
}

