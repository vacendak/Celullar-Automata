#include <stdio.h>                  // Incluímos la librerías necesarias para el programa.
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "libguardaimagen.h"        // la librería propia que guarda la imagen.

#define REGLA 182                   // Regla del ACE.
#define N 1000                      // Número de celdas del ACE.
#define T 500                       // Número de pasos de evolución.

int main(int argc, char *argv[])    // Función principal del programa.
{
    int i,j,nv;                     // Declaración de variables.
    int ACE[T+1][N+2];


    for(i=0;i<T+1;i++)              // Bucle para generación de la rejilla inicial del ACE.
    {
        for(j=0;j<N+2;j++)
        {
            ACE[i][j]=0;
        }
    }
    ACE[0][N/2]=1;                  // Colocación de la semilla en la mitad de la primera línea.

    for(i=1;i<T+1;i++)              // Bucle para generación del ACE.
    {
        for(j=1;j<N+1;j++)
        {
            nv=(ACE[i-1][j+1]|ACE[i-1][j]<<1|ACE[i-1][j-1]<<2);
            ACE[i][j]=(REGLA>>nv)&1;
        }
        ACE[i][0]=ACE[i][N];        // Actualización de las condiciones periódicas de contorno.
        ACE[i][N+1]=ACE[i][1];
    }

    guardaPGMi("ACE_01_R182.pgm",N+2,T+1,(int*)ACE,1,0);    // Función para guardar la imagen.

    return 0;
    system("pause");
}
