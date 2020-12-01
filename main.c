#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

static void sighandler(int signo){
    
    if (signo == SIGINT){
        int file = open ("file", O_WRONLY | O_CREAT | O_APPEND, 0644);
        
        if (file == -1){
            printf("ERROR %d: %s", errno, strerror(errno));
        }
        
        char message[] = "Program exited due to SIGINT\n";
        write(file, message, sizeof(message));
        close(file);
        exit(0);
    }
    
    if (signo == SIGUSR1){
        printf("Parent PID: %d\n", getppid());
    }
    
}

// runs in a forever while loop
int main(){
    signal(SIGINT, sighandler); // signal: attach a signal to a signal handling function
    signal(SIGUSR1, sighandler);

    while (1){
        printf("PID: %d\n", getpid()); // print PID
        sleep(1); // causes the program to wait 1 second between inner loop iterations
    }
    return 0;
}


