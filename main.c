#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //fork
#include <sys/types.h> // pid_t
#include <sys/wait.h> // For waitpid()

int main(){
    char *line = NULL;
    size_t len = 0;
    size_t nread;
    
    while(1){
        printf("$ ");
        fflush(stdout);
        nread = getline(&line, &len, stdin);
        if(nread == -1){
            printf("\n");
            break;
        }
        line[strcspn(line, "\n")] = 0;
        if(strcmp(line, "exit") == 0){
            break;
        }else{
            // parsing the command
            char *argv[100];
            char *token;
            int i = 0;

            token = strtok(line, " ");
            while(token != NULL){
                argv[i] = token;
                i++;
                token = strtok(NULL, " ");
            }
            argv[i] = NULL;

            // empty command
            if (argv[0] == NULL) {
                continue;
            }
            pid_t pid = fork();  // sys call to create a new process, duplicating the calling process
            // printf("pid: %d\n", pid);
            if(pid < 0){
                // forking failed
                perror("fork"); // fun to print sys call errors
            }else if(pid == 0){  // child process
                if (execvp(argv[0], argv) == -1) {
                    // If execvp returns, an error occurred
                    perror(argv[0]);
                    exit(EXIT_FAILURE); // Exit the child with an error status, inbult macro
                }
            }else{
                int status;
                waitpid(pid, &status, 0); // status - child process info, 0 - default beh, exit when child ends
                printf("This is the parent process. I created a child with PID: %d\n", pid);
            }
        }
    }
    free(line);

    return 0;
}