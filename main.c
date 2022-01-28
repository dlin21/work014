#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

static void sighandler(int signo){
  if (signo == SIGINT){
    int file = open("log.txt", O_CREAT | O_WRONLY, O_APPEND, 0644);
    if(file == -1){
      printf("error: %s\n", strerror(errno));
      exit(0);
    }

    char path[100] = "Program exited due to SIGINT\n";
    int err = write(file, path, sizeof(path));
    if (err == -1){
      printf("%s\n", strerror(errno));
      return;
    }
    exit(0);
  }
  
  if(signo == SIGUSR1) printf("PPID: %d\n", getppid());
  
}

int main(){
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while(1){
    printf("PID: %d\n", getpid());
    sleep(1);
  }
  return 0;
}
