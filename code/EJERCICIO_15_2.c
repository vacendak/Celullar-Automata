#include <stdio.h>              //Inclu�mos las librer�as necesarias para el programa.
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "libguardaimagen.h"    //Librer�a propia que guarda la imagen generada.

#define REGLA 126       //Regla del ACE.
#define N 500           //N�mero de celdas del ACE.
#define T 500           //N�mero de pasos de evoluci�n.

int main(int argc, char** argv)     //Funci�n principal del programa.
{
    int i,j,nv,n;           //Declaraci�n de variables.
    int ACE[T+1][N+2];      //Declaraci�n del ACE con sus dimensiones.

    srand(time(NULL));      //Definici�n de la semilla aleatoria referenciada al reloj de la CPU.

    for(i=0;i<T+1;i++)      //Bucle para inicializar la rejilla del ACE.
        {
        for(j=0;j<N+2;j++);
            {
                ACE [i][j]=0;
            }
        }

    for (n=0;n<N+1;n++)     //Bucle para la generaci�n aleatoria de la primera fila del ACE.
    {
        if (((double)rand())/((RAND_MAX)+1.0)<0.5)
            ACE[0][n]=0;
        else
            ACE[0][n]=1;
    }

    for(i=1;i<T+1;i++)      //Bucle para la generaci�n del resto del ACE.
    {
        for(j=1;j<N+1;j++)
        {
            nv=(ACE[i-1][j+1]|ACE[i-1][j]<<1|ACE[i-1][j-1]<<2);
            ACE[i][j]=(REGLA>>nv)&1;
        }
        ACE[i][0]=ACE[i][N];    //Actualizaci�n de las condiciones peri�dicas de contorno.
        ACE[i][N+1]=ACE[i][1];
    }
    guardaPGMi("ACE_02_R126.pgm",N+2,T+1,(int*)ACE,1,0); //Funci�n que guarda la imagen del ACE.

    return 0;
}
