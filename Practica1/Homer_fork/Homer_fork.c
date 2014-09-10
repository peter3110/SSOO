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
	printf("Abraham es padre de Homer\n");
    int Abraham = fork();
    wait(0);				// no termines el proceso padre hasta que no haya terminado el proceso hijo
    
    if (Abraham == 0) {
        /* Esto lo ejecuta sólo el hijo Homer. */
        
		int Bart = fork();
		if(Bart != 0) printf("Homer es padre de Bart\n");
		else exit(0);
		
		int Lisa = fork(); 
		if(Lisa != 0) printf("Homer es padre de Lisa\n");
		else exit(0);
		
		int Magee = fork();
		if(Magee != 0 )printf("Homer es padre de Magee\n");
		else exit(0);
		
        
    } else {exit(0); }
    
    return 0;
}
