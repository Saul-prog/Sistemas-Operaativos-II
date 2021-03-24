#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define ARG_OBLIGATORIOS 1
void recorrerDirectorioR(const char * nombre){
    DIR * pDir;
    struct dirent *pEnt;
    pDir=opendir(nombre);
    pEnt=readdir(pDir);
    while(pEnt!=NULL){
    if(pEnt->d_type==DT_DIR){
        if((strcmp((pEnt->d_name),".")!=0)&&(strcmp((pEnt->d_name),"..")!=0)){
            if(chdir(pEnt->d_name)==-1){
                fprintf(stderr,"Error al cambiar de directorio: \t");
                perror("");
            }else{
                recorrerDirectorioR(".");
                chdir("..");
            }
        }
    }
        if((strcmp((pEnt->d_name),".")!=0)&&(strcmp((pEnt->d_name),"..")!=0)){
        fprintf(stdout,"El nombre del archivo es: %s\n\t Inodo: %ld\n", pEnt->d_name,pEnt->d_ino);
        }
        pEnt=readdir(pDir);
    }
    closedir(pDir);
}
int main(int argc, char const *argv[])
{
    if(argc<=ARG_OBLIGATORIOS){
        fprintf(stderr, "Al menos dos nombres de ficheros\n");
        return 1;
    }//if
    int i,recursivo=0;
    DIR * pDir;
    struct dirent *pEnt;

    for ( i = 0; i < argc; i++)
    {
        if(argv[i][0]=='-'&&argv[i][1]=='r'){
            recursivo=1;
        }
    }
    
    if(recursivo ==0){
        pDir=opendir(argv[1]);
        pEnt=readdir(pDir);
        while(pEnt!=NULL){
            fprintf(stdout,"El nombre del archivo es: %s\n\t Inodo: %ld\n", pEnt->d_name,pEnt->d_ino);
            pEnt=readdir(pDir);
        }
        closedir(pDir);
    }else{
        recorrerDirectorioR(argv[1]);
    }
    
    return 0;
}
