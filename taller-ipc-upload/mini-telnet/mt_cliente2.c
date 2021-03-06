
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define SOCK_PATH "mi_socket"
#define MENSAJE_MAXIMO 1024

int main(int argc, char **argv) {
    
    char *ip_server = argv[1];
    char buf[MENSAJE_MAXIMO], buf2[MENSAJE_MAXIMO];
    int s = socket(AF_INET, SOCK_STREAM, 0), n;
    struct sockaddr_in remote;
    int ip = inet_aton(ip_server, &remote.sin_addr);

    remote.sin_family = AF_INET;
    remote.sin_port = htons(5551);

   	/* Conectarse. */
    //len = sizeof(remote.sin_family);
    if (connect(s, (struct sockaddr *)&remote, sizeof(remote)) == -1) {
        perror("conectandose");
        exit(1);
    }

    /* Mandando por el socket lo que me pasan por consola */
    while(printf("> "), fgets(buf, MENSAJE_MAXIMO, stdin), !feof(stdin)) {
	if(strcmp(buf, "chau\n")==0) { break;}
        if (sendto(s, buf, strlen(buf)+1, 0, (struct sockaddr*)&remote, sizeof(remote)) == -1) {
            perror("enviando");
            exit(1);
        }
        n = recv(s, buf2, MENSAJE_MAXIMO, 0);
        if (n == 0) 
            break;
        if (n < 0) { 
        	perror("recibiendo");
        	exit(1);
        }
	buf2[n] = '\0';
		printf("%s", buf2);
    }

    /* Cerrar el socket. */
    close(s);

    return 0;
}
