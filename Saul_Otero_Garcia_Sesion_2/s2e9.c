#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define ARG_OBLIGATORIOS 2

int validar_num(char const *numero){
    int i;
    for ( i = 0; i < strlen(numero); i++)
    {
        if(!(isdigit(numero[i]))){
            fprintf(stderr, "Introduzca solo numeros en el segundo argumento\n");
            return 1;
        }
    }
    return 0;
}
int main(int argc, char const *argv[])
{ 
    struct stat sb;
    int cho,numero;
    if(argc<=ARG_OBLIGATORIOS){
        fprintf(stderr, "Introduzca un nombre de un fichero y el grupo alq ue desee cambiarlo.\n");
        return 1;
    }//if
    
    
    if(validar_num(argv[2])==0){
        numero=atoi(argv[2]);
    stat( argv[1], &sb) ;
    
    if( S_ISREG( sb.st_mode ) == 0 ){
        cho= chown(argv[1], -1, numero);
        
        if(cho<0){
            fprintf(stderr,"Error al cambiar el grupo\n");
            perror("");
            return 1;
        }
    }
    if (S_ISLNK(sb.st_mode)==0){
        cho= lchown(argv[1], -1, numero);
        if(cho<0){
            fprintf(stderr,"Error al cambiar el grupo\n");
            perror("");
            return 1;
        }
    }

    }
    
    
    
    return 0;
}