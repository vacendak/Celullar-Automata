#include <stdio.h>      //  Incluímos las liberías necesarias para el programa.
#include <stdlib.h>
#include <math.h>

#define REGLA 126       //  Regla del ACE.
#define N 10            //  Número de celdas del ACE.
#define T 20            //  Númaro de pasos de evolución.


int main(int argc, char *argv[])    //Función principal del programa.
{
    int i, j, nv, estado, num_estado, cont;     //  Declaración de variables.
    int ACE[T+1][N+2];      //  Declaración del ACE, con sus dimensiones.

    int prob[T+1][(int) pow(2,N)];  /*  Definimos la matriz que almacenará  */
                                    /*  el número de veces que se repita    */
    for(i=0;i<T+1;i++)              /*  en el tiempo.                       */
    {
        for(j=0;j<pow(2,N);j++)
        {
            prob[i][j]=0;
        }
    }
    for(estado=0;estado<pow(2,N);estado++)  //  Bucle que inicializa los estados.
    {
        num_estado=0;

        for(j=N-1;j>=0;j--)     //  Bucle que inicializa el ACE.
        {
            ACE[0][N-j]=(estado>>j) & 1;

            num_estado+=ACE[0][N-j]*pow(2,j);   //  Cálculo del número de estado.
        }
        prob[0][num_estado]++;      //  Añadimos una entrada al contador de estado.

        ACE[0][0]=ACE[0][N];        //  Actualizamos las condiciones periódicas de contorno.
        ACE[0][N+1]=ACE[0][1];

        for(i=1;i<T+1;i++)      //  Bucle que simula las T primeros pasos del ACE.
        {
            num_estado=0;
            for(j=1;j<N+1;j++)
            {
                nv=(ACE[i-1][j+1]|ACE[i-1][j]<<1|ACE[i-1][j-1]<<2);
                ACE[i][j]=(REGLA>>nv) & 1;
                num_estado+=ACE[i][j] * pow(2,N-j);
            }

            prob[i][num_estado]++;

            ACE[i][0]=ACE[i][N];    // Actualizamos las condiciones periódicas de contorno.
            ACE[i][N+1]=ACE[i][1];
        }
    }

    for(i=0;i<T+1;i++)      //  Bucle para comprobar que la simulación ha sido correcta.
    {
        cont=0;
        for(j=0;j<pow(2,N);j++)
        {
            cont+=prob[i][j];
        }
        if(cont != pow(2,N))
            printf("\tERROR EN EL PASO %d\n", i);
    }

    FILE* atr;      //  Definimos y abrimos el archivo que va a almacenar los estados visitados.
    atr=fopen("atractor_REGLA.dat", "w");

    if (atr == NULL)    //  Bucle para verificar la apertura del archivo exitosa.
    {
        printf("No se ha podido abrir 'atractor_REGLA.dat' para escritura. Saliendo...\n");
        exit(1);
    }

    for(i=0;i<T+1;i++)  //  Bucle que guarda en el archivo los estados visitados alguna vez.
    {
        for(j=0;j<pow(2,N);j++)
        {
            if(prob[i][j]!=0)
                fprintf(atr, " %d\t%d\n", j, i);
        }
    }
    fclose(atr);    //  Orden para cerrar el archivo una vez escrito.

    return 0;
}
