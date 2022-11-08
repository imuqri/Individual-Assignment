#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	
	float currentSaving;
	printf("Enter your current ASB saving : ");
	scanf("%f", &currentSaving);
	
	printf( "Your current ASB saving is: %f", currentSaving);
	
	return 0;

}