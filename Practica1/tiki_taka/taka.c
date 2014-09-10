#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     27

main()
{
    int shmid;
    key_t key;
    char *shm, *s;

	/* Tenemos que saber cuál es el segmento compartido */
    key = 5678;

    /* Ubicamos el segmento */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /* Agregamos el segmento al espacio de datos */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    /* Leemos lo que hay en el espacio de datos */
    printf("%i\n", *(shm+1));
    while(1) {
		*shm = *shm + 10;
		printf("%i\n", *shm);
		int temp = *shm;
		while(*shm == temp) {sleep(1); }
		if(*shm > 100) {break;}
	}
	
    exit(0);
}
