#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define lbuff 1
#define ARG_OBLIGATORIOS 1




int main(int argc, char const *argv[])
{
    int error=0 ;
    int fd,i,cambios=0;
    char buffer[lbuff];
    ssize_t leido;//cantidad de leidos
    if(argc<=ARG_OBLIGATORIOS){//al menos un argumento a parte del argumento de indice 0
        fprintf(stderr,"Error, Introduzca un  parámetro\n");
        return 1;
    }//if

        fd=open(argv[1],O_RDONLY);
        if(fd==-1){
            
            fprintf(stderr, "Error al abrir el fichero %s: ",argv[1]);
            perror("");
            error++;
        }else{
            leido=read(fd,buffer,sizeof(*buffer)*lbuff);
            while(leido>0){
                for ( i = 0; i < leido; i++)
                {
                    if(buffer[i]=='a'){
                        buffer[i]='o';
                        cambios++;
                    }
                    fprintf(stdout, "%s", buffer);
                }         
                leido=read(fd,buffer,sizeof(*buffer)*lbuff);
            }
            if(leido<0){
                    fprintf(stderr,"Error al leer: ");
                    perror("");
            }
            close(fd);
            fprintf(stdout,"Cambios %d\n",cambios);
        }

return 0;
}
