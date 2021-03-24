#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define ARG_OBLIGATORIOS 2


int main(int argc, char const *argv[])
{
    int i,err;
    struct stat *buf;
    buf =malloc (256);
    if(argc<=ARG_OBLIGATORIOS){//al menos un argumento a parte del argumento de indice 0
        fprintf(stderr,"Error, Introduzca al menos un parámetro\n");
        return 1;
    }//if
    for ( i = 1; i < argc; i++)
    {
        err= stat(argv[i], buf);
        if(err<0){
            fprintf(stderr, "Error al consultar los datos de %s\n", argv[i]);
            perror("");
        }else{
            fprintf(stdout,"El archivo %s tiene una longitud de %ld bytes\n", argv[i],buf->st_size);
        }
    }
    
 
 
    return 0;
}
