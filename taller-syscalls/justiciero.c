#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <syscall.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int pid;
    
    pid=fork();
    if (pid == -1)
          perror("creando proceso hijo");

    if (pid == 0) {
        /* Esto lo ejecuta sólo el hijo. */
        //printf("Yo soy el hijo.\n");
        if(ptrace(PTRACE_TRACEME, 0, NULL, NULL))
        {
            perror("ERROR child ptrace(PTRACE_TRACEME, ...)"); _exit(1);
        }
        execvp(argv[1], argv+1);
    } else {
        /* Esto lo ejecuta sólo el padre. */
        //printf("Yo soy el padre, mi hijo tiene pid %d.\n", pid);
        
          int status;
        while(1) {
            if(wait(&status) < 0) { perror("wait"); break; }
            if(WIFEXITED(status)) break;
            
            int data = ptrace(PTRACE_PEEKUSER, pid, 8*ORIG_RAX, NULL);
            
		//printf("%i\n", data);
            if(data == SYS_kill)
            {
                printf("Se ha hecho justicia!\n");
                ptrace(PTRACE_KILL, pid, NULL, NULL);
		break;
            }
            ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
        }
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
    }
    
    return 0;
}
