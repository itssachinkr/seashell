#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            printf("Command: %s\n", argv[0]);
            for(int j=1; j<i; j++){
                printf("Argument %d: %s\n", j, argv[j]);
            }

        }
    }
    free(line);

    return 0;
}