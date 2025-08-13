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
            printf("command not found: %s\n", line);
        }
    }
    free(line);

    return 0;
}