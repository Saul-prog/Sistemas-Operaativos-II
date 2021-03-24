/*Realiza un programa que al ser ejecutado cree un fichero en el directorio activo 
con el nombre “ejecutor” 
(si ya existe que lo haga de nuevo), escriba dentro el texto 
[echo “Archivo ejecutado desde un proceso...”] (sin los corchetes) y lo cierre. 
Luego dará al fichero creado el permiso de ejecución y ordenará su ejecución utilizando la 
llamada del sistema correspondiente (consultar la función “system”, pero sólo por esta vez). */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int fd,cambio;
    char *pathname="ejecutor.sh";
    ssize_t escrito;
    char mensaje[]="echo \"Archivo ejecutado desde un proceso...\"";
   
    fd=open(pathname, O_CREAT | O_WRONLY, 0666);
    if (fd<0)
    {
        fprintf(stderr,"Error, No se ha podido crear\n");
        perror("");
        return -1;
    }
    escrito=write(fd, mensaje, strlen(mensaje));
    if(escrito<0){
        fprintf(stderr,"Error, No se ha podido escribir\n");
        perror("");
        return -1;
    }
    close(fd);
    
    cambio=chmod(pathname, 0777);
    if(cambio<0){
        fprintf(stderr,"Error al cambiar de permiso");
        perror("");
    }
    system("bash ejecutor.sh");
    return 0;
}

