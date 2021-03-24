#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define ARG_OBLIGATORIOS 2


int main(int argc, char const *argv[])
{ 
    int j,i,debil,fuerte, errores=0;
    struct stat sb;
    if(argc<=ARG_OBLIGATORIOS){
        fprintf(stderr, "Al menos dos nombres de ficheros\n");
        return 1;
    }//if
    
    

    
    for(i=2;i<argc;i++){
        stat( argv[i], &sb) ; // Check the return value of stat

        if( S_ISREG( sb.st_mode ) == 0 )
        {
            if(i%2==0){
            //Simbolicos
            debil =symlink(argv[1], argv[i]);
                if(debil==-1){
                    fprintf(stderr,"Error al crear un enlace simbolico debil\n");
                    perror("");
                    errores++;
                }

            }else{
            //Fuertes
            fuerte= link(argv[1], argv[i]);
                if(fuerte==-1){
                    fprintf(stderr,"Error al crear un enlace simbolico debil\n");
                    perror("");
                    errores++;
                }
        }
        }else{
            fprintf(stdout, "%s No es un fichero", argv[i] ) ;
            errores++;
        }

                    
    }




return errores;
}