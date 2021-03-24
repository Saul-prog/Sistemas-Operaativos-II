#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

#define ARG_OBLIGATORIOS 1

char * formatdate(char* str, time_t val)
{
        strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
        return str;
}

int main(int argc, char const *argv[])
{
    if(argc<=ARG_OBLIGATORIOS){
        fprintf(stderr, "Al menos un directorio\n");
        return 1;
    }//if
    int semana=604800;
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    fprintf(stdout, "%ld", time(0));
    int resultado;
    resultado=time(0)-semana;

    DIR * pDir;
    struct dirent *pEnt;
    char date[36];
    pDir=opendir(argv[1]);
        pEnt=readdir(pDir);
        struct stat sb;
        while(pEnt!=NULL){
            stat(pEnt->d_name , &sb) ;

            if(sb.st_mtime<resultado){
             fprintf(stdout,"El nombre del archivo es: %s\n", pEnt->d_name);
            //dev_t     st_dev;     /* ID of device containing file */
            fprintf(stdout,"\tID: %ld\n", sb.st_dev);
            //ino_t     st_ino;     /* inode number */
            fprintf(stdout,"\tiNodo: %ld\n", sb.st_ino);
            //mode_t    st_mode;    /* protection */
            fprintf(stdout,"\tProtección: %d\n", sb.st_mode);
            //nlink_t   st_nlink;   /* number of hard links */
            fprintf(stdout,"\tNúmero de enlaces fuertes: %ld\n", sb.st_nlink);
            //uid_t     st_uid;     /* user ID of owner */
            fprintf(stdout,"\tNúmero de id del usuario: %d\n", sb.st_uid);
            //gid_t     st_gid;     /* group ID of owner */
            fprintf(stdout,"\tNúmero de id del grupo: %d\n", sb.st_gid);
            //dev_t     st_rdev;    /* device ID (if special file) */
            fprintf(stdout,"\tNúmero de id si es un fichero especial: %ld\n", sb.st_rdev);
            //off_t     st_size;    /* total size, in bytes */
            fprintf(stdout,"\tTamaño total ne bytes: %ld\n", sb.st_size);
            //blksize_t st_blksize; /* blocksize for file system I/O */
            fprintf(stdout,"\tTAmaño del bloque para I/O del sistema de ficheros: %ld\n", sb.st_blksize);
            //blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
            fprintf(stdout,"\tNúmero bloques de 512B asignados: %ld\n", sb.st_blocks);
            //time_t    st_atime;   /* time of last access */
            fprintf(stdout,"\tÚltimo acceso: %s\n", formatdate(date, sb.st_atime));
            //time_t    st_mtime;   /* time of last modification */
            fprintf(stdout,"\tÚltima modificación: %s\n", formatdate(date, sb.st_mtime));
            //time_t    st_ctime;   /* time of last status change */
            fprintf(stdout,"\tÚltima cambio de estado: %s\n", formatdate(date, sb.st_ctime));
            }
            
            
            
            pEnt=readdir(pDir);
        }
        closedir(pDir);
        

    return 0;
}