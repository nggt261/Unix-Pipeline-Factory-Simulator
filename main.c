#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct{
    int item_id;
    double generation_timestamp;
}Material;

int main(){
    //for holding read/write file desc
    int pipe_a[2]; //supplier a to pkg
    int pipe_b[2]; //same here

    if(pipe(pipe_a)==-1){
        perror("Pipe A malfunctioned");
        exit(1);
    }
    if(pipe(pipe_b)==-1){
        perror("Pipe B malfunctioned");
        exit(1);
    }
    printf("Pipes laid down. Factory ready to boot\n");

    printf("Booting machines...\n");

    //Supplier A
    pid_t pid_a=fork();
    if(pid_a==0){
        close(pipe_a[0]); //lock read door of A
        close(pipe_b[0]); //lock read door of B
        close(pipe_b[1]); //lock write door of B

        printf("Supplier A online. Ready to generate material.\n");
        exit(0);
    }

    //Supplier B
    pid_t pid_b=fork();
    if(pid_b==0){
        close(pipe_b[0]);
        close(pipe_a[0]);
        close(pipe_a[1]);
        printf("Supplier B online. Ready to generate material.\n");
        exit(0);
    }

    //Packager
    pid_t pid_Packager=fork();
    if(pid_Packager==0){
        close(pipe_a[1]);
        close(pipe_b[1]);
        printf("Packager online. Waiting for raw materials...\n");
        exit(0);
    }

    //Factory Manager
    //parent process, doesnt build anything just watches
    close(pipe_a[0]); close(pipe_a[1]); //closes all pipes immediately
    close(pipe_b[0]); close(pipe_b[1]);
    //shift end
    waitpid(pid_a, NULL, 0);
    waitpid(pid_b, NULL, 0);
    waitpid(pid_Packager, NULL, 0);
    printf("Factory closed.\n");
    
    return 0;
}