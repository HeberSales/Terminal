#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <sys/wait.h>

int main(int argc, char *argv[]){
    
    pid_t pid;
    int MaximoLinhas = 256, MaximoArgumentos = 48, numerosArgumentos = 0, status; 
    char buffer[MaximoLinhas], *args[MaximoArgumentos], *temp1, *temp2;

    printf("Terminal\n");
    printf("Para sair pressione Ctrl + D :\n");
    while(fgets(buffer, MaximoLinhas, stdin) != NULL) {
        if(buffer[strlen(buffer) - 1] == '\n'){
            buffer[strlen(buffer) - 1] = 0;
        }
        temp1=strdup(buffer);
        for(int i=0; ;i++,temp1 = NULL){
            temp2=strtok(temp1," ");
            if(temp2==NULL){
                break;
            }
            args[i]=temp2;
            numerosArgumentos+=1;
        }
        free(temp1);
        args[numerosArgumentos]=(char *)NULL;
        pid=fork();
        if(pid==0){
            execvp(args[0], &args[0]);
            printf("não pode executar: %s", buffer);
            exit(127);
        }
        printf("*****");
    }
    exit(EXIT_SUCCESS);
}