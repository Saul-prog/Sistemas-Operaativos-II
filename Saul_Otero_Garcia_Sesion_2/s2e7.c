#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h> 

#include <fcntl.h>

#define ARG_OBLIGATORIOS 1
#define lbuff 256

int main(int argc, char const *argv[])
{
    int tam_pagina= sysconf(_SC_PAGE_SIZE);//el sistema devuelve el tamanho de la pagina
    int i, fd,fd2,bytes, pendiente,resultado=0;
    off_t longitud;
    int *cambios;       
    char *buffer;
    off_t posicion= 0;
    char copia[20];
    ssize_t leido,escrito;
    buffer= malloc( lbuff);
    if(argc<=ARG_OBLIGATORIOS){//al menos un argumento a parte del argumento de indice 0
        fprintf(stderr,"Error, Introduzca al menos un parámetro\n");
        return 1;
    }//if

    //Crear la copia***********************************************************
    sprintf(copia, "%s.copia",argv[1]);
    fd=open(argv[1],O_RDONLY);
        if(fd==-1){
            
            fprintf(stderr, "Error al abrir el fichero %s: \n",argv[1]);
            perror("");
            
        }
        fprintf(stdout,"Copia: %s",copia);
    fd2=open(copia,O_CREAT|O_WRONLY|O_TRUNC,0666);
        if(fd==-1){
            
            fprintf(stderr, "Error al abrir el fichero %s: \n",argv[2]);
            perror("");
            
        }
      
            
            leido=read(fd,buffer,sizeof(*buffer)*lbuff);
                    while(leido>0){
                        escrito= write(fd2, buffer, leido);
                    
                        leido=read(fd,buffer,sizeof(*buffer)*lbuff);
                    }
                    if(leido<0){
                            fprintf(stderr,"Error al leer: ");
                            perror("");
                    }
            close(fd);
            close(fd2);
    //se proyecta en memoria****************************************************************************
    fd=open(copia, O_RDWR);
    lseek(fd,0,SEEK_SET);
    longitud= lseek(fd,0,SEEK_END);
    *cambios=0;
    if(longitud==-1){
        fprintf(stderr,"Error al posicionar el puntero\n");
        perror("");
        return -1;
    }
    while( (posicion < longitud) && (resultado == 0) )
    {
        bytes= tam_pagina;
        pendiente= longitud-posicion;

        if(bytes>pendiente)
            bytes= pendiente;

        buffer= mmap(NULL, bytes,PROT_READ | PROT_WRITE, MAP_SHARED, fd, posicion);
        
        
        if(buffer != MAP_FAILED)
        {
            
            for(i=0; i<bytes;i++)
            {
                if(buffer[i] == 'a')
                {
                    buffer[i]='o';
                    (*cambios)++;
                }
                printf("%c",buffer[i]);
            }//for
            
            //Incremento la posision ("bytes" o "tam_pagina")
            posicion+= bytes;
            
            //Liberar la proyeccion 
            //  0:exito -1:fallo
            resultado= munmap(buffer, bytes);
            if(resultado==-1){
                fprintf(stderr,"Fallo al eliminar el mapeado");
                perror("");
                return -1;
            }
        }else{
            fprintf(stderr,"Fallo al mapear");
            perror("");
            return -1;
        }
    }
    printf("\n");
    return 0;
}
