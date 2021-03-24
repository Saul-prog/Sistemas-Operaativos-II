#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>


#define ARG_OBLIGATORIOS 2


int main(int argc, char const *argv[])
{
    
    int i,j,k, cambio,fd, creado;
    char *cad;
    char *buff="ABCDEFGHIJKLMNOPQRSTVWXYZ";
    ssize_t escrito;
    char *ruta_activa;
    DIR *pDir;
    struct dirent *pEnt;
    
    int numero;
    
    
    
    if(argc<=ARG_OBLIGATORIOS){
        fprintf(stderr, "Introduzca un directorio y el número de copias\n");
        return 1;
    }//if
    numero=atoi(argv[2]);
    if(numero<3 || numero>30){
        fprintf(stdout, "El número ha de estar comprendido entre 3 y 30");
        return -1;
    }
    ruta_activa=getcwd(NULL,0);
    creado=mkdir(argv[1],0777);
    if(creado<0)
    {
    	fprintf(stderr, "Error al crear el directorio");
    	perror("");
    	return -1;
    }
    cambio =chdir(argv[1]);
    
    for ( i = 1; i < numero+1; i++)
    {
        
        sprintf(cad, "Datos%i.txt",i);
       
        fd=open(cad, O_CREAT|O_WRONLY|O_TRUNC,0666);
        if(fd<0){
            fprintf(stderr, "Error al abrir/crear el archivo %s", argv[i]);
            perror("");
        }
        for (j = 0; j < i; j++)
        {
            for (k = 0; k < 10; k++)
            {
                escrito= write(fd, buff, sizeof(buff)*3+1);
                if(escrito<0){
                    fprintf(stderr, "Error al escribir");
                    perror("");
                }
            }
            
        }
        close(fd);
    }
    
    chdir(ruta_activa);
    pDir = opendir (argv[1]);            
    if (pDir == NULL){
        fprintf(stderr, "No puedo abrir el directorio");
        perror("");
    }
    pEnt=readdir(pDir);
    
    
    while (pEnt!= NULL){
    
     if((strcmp((pEnt->d_name),".")!=0)&&(strcmp((pEnt->d_name),"..")!=0)){
		/* Si pongo estas tres lineas el script falla, si escribo "struct stat sb;" sin usarlo en ningun sitio, solo por declararlo da error
		    struct stat sb;
    		stat(pEnt->d_name, &sb);
    	   	fprintf(stdout, "Tamaño %ld", sb.st_size);*/
            	fprintf(stdout,"El nombre del archivo es: %s\n\t Inodo: %ld\n", pEnt->d_name,pEnt->d_ino);
            	
        }
        pEnt=readdir(pDir);
    }
    closedir (pDir);
    free(ruta_activa);
    return 0;
}
