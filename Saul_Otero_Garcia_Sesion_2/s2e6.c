/*Realizar un programa que deberá admitir un argumento, 
que será el nombre de un archivo, el cual abrirá para lectura y escritura,
mostrará en pantalla que va a bloquear el archivo, y tras esto activará 
un bloqueo sobre los 20 primeros bytes del mismo, 
esperará unos 25 segundos más un número aleatorio entre 5 y 15 segundos 
(usar por esta vez la función “sleep”), 
y cuando continúe mostrará en pantalla que va a desbloquear el archivo, 
liberará el bloqueo, y terminará cerrando el fichero.*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define ARG_OBLIGATORIOS 1



int main(int argc, char const *argv[])
{
    int fd,bloqueo, aleatorio;
    off_t punt;
    srand(time(NULL));
    aleatorio=25+ rand()%(15+1-5)+5;
    if(argc<=ARG_OBLIGATORIOS){
        fprintf(stderr, "Introduzca al menos un fichero\n");
        return 1;
    }//if
    fd=open(argv[1],O_RDWR);
    if(fd<0){
        fprintf(stderr,"Error al abrir el fichero %s", argv[1]);
        perror("");
        return -1;
    }
    fprintf(stdout,"Se va a proceder al bloqueo de los primeros 20 bytes de %s\n", argv[1]);
    bloqueo=lockf(fd,F_LOCK,20);
    if(bloqueo<0){
        fprintf(stderr,"Error al bloquear");
        perror("");
        return -1;
    }
    
    sleep(aleatorio);
    fprintf(stdout, "Se va a proceder a desbloquear\n");
    punt=lseek( fd, SEEK_SET, 0);
    if(punt<0){
        fprintf(stderr,"Error al reposicionar el puntero");
        perror("");
        return -1;
    }
    bloqueo=lockf(fd,F_ULOCK,20);
    if(bloqueo<0){
        fprintf(stderr,"Error al bloquear");
        perror("");
        return -1;
    }
    return 0;
}
