#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

main() {		// PROCESO 2
	
	/* Definimos cuál es nuestro segmento de memoria compartida */
	int shmid;
    key_t key = 5678;
    int *shm;
	
	/* Creamos el segmento de memoria compartida */
	if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget"); exit(1);
    }
    
    /* Agregamos el segmento a nuestro espacio de datos */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat"); exit(1);
    }
    
    /* Escribimos algo en el espacio de memoria compartida */
    *shm = 1; *(shm+1) = 1; *(shm+2) = 100;
    /* Esperamos a que el otro proceso escriba algo */
	while(1) {
		int temp = *shm;
		while(*shm == temp) {sleep(1); }
		*shm = *shm + 5;
		printf("%i\n", *shm);
		if(*shm > *(shm+2)) {break;}
	}
    exit(0);
    
}
