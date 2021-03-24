#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ARG_OBLIGATORIOS 1


int main(int argc, char const *argv[])
{
    int i,error=0 ;
    int fd;
    off_t longitud;
    if(argc<=ARG_OBLIGATORIOS){//al menos un argumento a parte del argumento de indice 0
        fprintf(stderr,"Error, Introduzca al menos un parámetro\n");
        return 1;
    }//if
    for (i = 1; i < argc; i++)
    {
        
        fd=open(argv[i],O_RDONLY);
        if(fd==-1){
            
            fprintf(stderr, "Error al abrir el fichero %s: ",argv[i]);
            perror("");
            error++;
        }else{
            longitud=lseek(fd,0,SEEK_END);
            if(longitud==-1){
                fprintf(stderr,"Error al leer el fichero: ");
                perror("");
                error++;
            }else{
                fprintf(stdout, "El fichero %s tiene una longitud de %ld \n", argv[i],longitud);
            }//if de longitud
            close(fd);
        }//if de abrir
        
    }//for
    
    return error;
}//main
