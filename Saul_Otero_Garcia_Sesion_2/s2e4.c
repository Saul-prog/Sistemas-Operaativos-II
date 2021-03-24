#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define lbuff 100
#define ARG_OBLIGATORIOS 2




int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int error=0 , numero;
    int fd,i,j,eliminado,escrito_total,total;
    char *buffer;
    buffer= malloc( lbuff);
    char aleatorio[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    ssize_t leido,escrito,total_escrito;//cantidad de leidos
    if(argc<ARG_OBLIGATORIOS){//al menos un argumento a parte del argumento de indice 0
        fprintf(stderr,"Error, Introduzca algún parámetro\n");
        return 1;
    }//if
    for (j = 1; j < argc; j++)
    {    
      fd=open(argv[j],O_RDWR);
        if(fd==-1){
            
            fprintf(stderr, "Error al abrir el fichero %s: \n",argv[j]);
            perror("");
            error++;
        }else{
            total=lseek(fd,0,SEEK_END); //Se calcula el tamaño total del primer fichero
            lseek( fd, 0, SEEK_SET);  //Se vuelve a poner el puntero al principio del fichero
            leido=read(fd,buffer,sizeof(*buffer)*lbuff); //Se lee algo de tamaño leido
            lseek( fd, 0, SEEK_SET);  //Se pone el puntero al principio para que escriba encima
            while(total>escrito_total){
                
                for ( i = 0; i < leido; i++)
                {
                    numero= rand() % ((int)strlen(aleatorio));
                    buffer[i]=aleatorio[numero];//se modifica el buffer
                }
                
                escrito= write(fd, buffer, leido); //se escribe el buffer en el fichero
                if(escrito<0){
                    fprintf(stderr,"Error al escribir: \n");
                    perror("");
                }
                escrito_total+=escrito;//se anota cuanto se ha escrito
                
                leido=read(fd,buffer,sizeof(*buffer)*lbuff); //se lee el siguiente bloque
                lseek( fd, escrito_total, SEEK_SET); //se da marcha atras para el que el bloque escriba encima de lo que se acaba de leer
            }
            fprintf(stdout, "Archivo modificado.\n");
            if(leido<0){
                    fprintf(stderr,"Error al leer: \n");
                    perror("");
            }
            close(fd);
          
            eliminado= unlink(argv[j]);
            if(eliminado!=0){
                fprintf(stderr,"Error al eliminar el archivo %s: \n", argv[j]);
                perror("");
            }else{
                fprintf(stdout,"Archivo eliminado.\n");
            }
            
        }
    }//for
    return error;
}//main
