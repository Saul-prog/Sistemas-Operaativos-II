#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h> 

#define ARG_OBLIGATORIOS 2

int validar_num(char const *numero){
    int i;
   
    for ( i = 0; i < strlen(numero); i++)
    {
        if(!(isdigit(numero[i]))){
            
            fprintf(stderr, "Introduzca solo numeros en el primer argumento\n");
            return 1;
        }else{
            if(i==0){
                if(numero[0]!='0'){
                    
                    return 1;
                }
            }
        }
        if(strlen(numero)>5){
            fprintf(stderr,"Valor demasiado largo debe ser 0xxx o 0xxxx\n");
            return 1;
        }
    }
    
    return 0;
}
int exponencial(int base, int exponente){
    int n,resultado=1;
    for(n=0;n<exponente;n++){
        resultado=base*resultado;
    }
   
    return resultado;
}
int convertOctalToDecimal(int octalNumber)
{
    int decimalNumber = 0, i = 0;
    int potencia;
    while(octalNumber != 0)
    {
        
        decimalNumber += (octalNumber%10) * exponencial(8,i);
        ++i;
        octalNumber/=10;
    }

    i = 1;

    return decimalNumber;
}

int main(int argc, char const *argv[])
{ 
    int numero,func,i,errores=0;
    long long decimal;
    char numeroc[6];
    if(argc<=ARG_OBLIGATORIOS){
        fprintf(stderr, "Introduzca un nombre de un fichero y el grupo alq ue desee cambiarlo.\n");
        return 1;
    }//if
    if(validar_num(argv[1])==0){
        numero=atoi(argv[1]);
        decimal=convertOctalToDecimal(numero);  //CAmbiar de octal a decimal
        
        for(i=2; i<argc; i++){
            
            func= chmod(argv[i], decimal);
            if(func==-1){
                fprintf(stderr, "Error al cambiar el permiso de acceso del argumento %s\n", argv[i]);
                perror("");
                errores++;
            }
        }
    }else{
        fprintf(stderr,"El primer valor ha de ser numérico, comenzando por 0\n");
        return 1;
    }
    
if(errores>0){
errores++;
}
return errores;
}
