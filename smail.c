#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void sigint_handler(int sig) {
    printf("\n invalid action! please enter your student ID");
}

int main()
{
    // First pipe send input string from parent
    // Second pipe store concatenated string from child
 
    int fd1[2]; // Used to store student ID
    int fd2[2]; // Used to store student email
    char fixed_str[] = {"@student.uitm.edu.my"};
    char input_str[100];
	pid_t p;
    void sigint_handler(int sig);
    
 
    if (pipe(fd1) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    if (pipe(fd2) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    if (signal(SIGINT, sigint_handler) == SIG_ERR){
        perror("signal");
        exit(1);
    }
	printf("Please enter your UiTM student ID: "); //prompt student to enter their student id
    scanf("%s", input_str);
    p = fork();
 
    if (p < 0) {
        fprintf(stderr, "fork Failed");
        return 1;
    }
 
    // Parent process
    else if (p > 0) {
        char concat_str[100];
 
        close(fd1[0]); // Close reading end of first pipe
 
        // Write input string and close writing end of first
        // pipe.
        write(fd1[1], input_str, strlen(input_str) + 1);
        close(fd1[1]);
 
        // Wait for child to send a string
        wait(NULL);
 
        
    }
 
    // child process
    else {
        close(fd1[1]); // Close writing end of first pipe
 
        // Read a string using first pipe
        char concat_str[100];
        read(fd1[0], concat_str, 100);
 
        // Concatenate a fixed string with it
        int k = strlen(concat_str);
        int i;
		
        for (i = 0; i < strlen(fixed_str); i++)
            concat_str[k++] = fixed_str[i];
 
        concat_str[k] = '\0'; // string ends with '\0'
 
        // Close both reading ends
        close(fd1[0]);
        close(fd2[0]);
 
        // Write concatenated string and close writing end
        write(fd2[1], concat_str, strlen(concat_str) + 1);
        close(fd2[1]);
		
		close(fd2[1]); // Close writing end of second pipe
 
        // Read string from child, print it and close
        // reading end.
        read(fd2[0], concat_str, 100);
        printf("Your generated UiTM studen email is : %s", concat_str);
        close(fd2[0]);
 
        exit(0);
    }
}

