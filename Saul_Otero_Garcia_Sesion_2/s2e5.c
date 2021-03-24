#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define ARG_OBLIGATORIOS 3



int main(int argc, char const *argv[])
{
    
    int fd,fd2,i,tam_fd1;
    int retraso =-1;
    int lbuff=1;
    char buffer[lbuff];
    
    ssize_t leido,escrito;
    if(argc<=ARG_OBLIGATORIOS){
        fprintf(stderr, "Introduzca primero un archivo del que se quiera copiar, el segundo un nombre para hacer la copia y por último la opción A, B o C\n");
        return 1;
    }//if
    
    if(argv[3][0] != 'A'&&argv[3][0] != 'B'&&argv[3][0] != 'C'){
        fprintf(stderr, "Introduzca primero un archivo del que se quiera copiar, el segundo un nombre para hacer la copia y por último la opción A, B o C\n");
        return 1;
    }
        fd=open(argv[1],O_RDONLY);
        if(fd==-1){
            
            fprintf(stderr, "Error al abrir el fichero %s: \n",argv[1]);
            perror("");
            
        }
        fd2=open(argv[2],O_CREAT|O_WRONLY|O_TRUNC,0666);
        if(fd==-1){
            
            fprintf(stderr, "Error al abrir el fichero %s: \n",argv[2]);
            perror("");
            
        }
        
        if(argv[3][0] == 'A')
        {
            
            fprintf(stdout, "Valor A");
        
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
        }
        if(argv[3][0] == 'B')
        {
            
            lbuff=1024;
            
            char buffer2[lbuff];
            
            leido=read(fd,buffer2,sizeof(*buffer2)*lbuff);
                    while(leido>0){
                        escrito= write(fd2, buffer2, leido);
                    
                        leido=read(fd,buffer2,sizeof(*buffer2)*lbuff);
                    }
                    if(leido<0){
                            fprintf(stderr,"Error al leer: ");
                            perror("");
                    }
            close(fd);
            close(fd2);
        }  
        if(argv[3][0] == 'C')
        {
            tam_fd1=lseek( fd, 0, SEEK_END); 
            if(tam_fd1==-1){
                fprintf(stderr,"Error al posicionar el puntero");
                perror("");
                return -1;}
            if(lseek( fd2, tam_fd1-1, SEEK_SET)==-1){
                fprintf(stderr,"Error al posicionar el puntero");
                perror("");
                return -1;
            }
            if(lseek( fd, 0, SEEK_SET)==-1){
                fprintf(stderr,"Error al posicionar el puntero");
                perror("");
                return -1;
            }
            leido=read(fd,buffer,sizeof(*buffer));
            while(leido>0){
                lseek( fd2, retraso, SEEK_END); 
                escrito= write(fd2, buffer, leido);
                retraso--;
                leido=read(fd,buffer,sizeof(*buffer));
            }
            if(leido<0){
                    fprintf(stderr,"Error al leer: ");
                    perror("");
            }
            close(fd);
            close(fd2);
        }
        
        
        
return 0;

    }
    
