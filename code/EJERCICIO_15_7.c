#include <stdio.h>      //  Inclu�mos las liber�as necesarias para el programa.
#include <stdlib.h>
#include <math.h>

#define REGLA 126       //  Regla del ACE.
#define N 10            //  N�mero de celdas del ACE.
#define T 20            //  N�maro de pasos de evoluci�n.


int main(int argc, char *argv[])    //Funci�n principal del programa.
{
    int i, j, nv, estado, num_estado, cont, nest;   //  Declaraci�n de variables.
    int ACE[T+1][N+2];      //  Declaraci�n del ACE, con sus dimensiones.
    float fracc;        //  Variable que almacena la fracci�n de estados visitados.

    int prob[T+1][(int) pow(2,N)];  /*  Definimos la matriz que almacenar�  */
                                    /*  el n�mero de veces que se repita    */
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

            num_estado+=ACE[0][N-j]*pow(2,j);   //  C�lculo del n�mero de estado.
        }
        prob[0][num_estado]++;      //  A�adimos una entrada al contador de estado.

        ACE[0][0]=ACE[0][N];        //  Actualizamos las condiciones peri�dicas de contorno.
        ACE[0][N+1]=ACE[0][1];

        for(i=1;i<T+1;i++)          //  Bucle que simula las T primeros pasos del ACE.
        {
            num_estado=0;
            for(j=1;j<N+1;j++)
            {
                nv=(ACE[i-1][j+1]|ACE[i-1][j]<<1|ACE[i-1][j-1]<<2);
                ACE[i][j]=(REGLA>>nv) & 1;
                num_estado+=ACE[i][j] * pow(2,N-j);
            }

            prob[i][num_estado]++;

            ACE[i][0]=ACE[i][N];    // Actualizamos las condiciones peri�dicas de contorno.
            ACE[i][N+1]=ACE[i][1];
        }
    }

    for(i=0;i<T+1;i++)      //  Bucle para comprobar que la simulaci�n ha sido correcta.
    {
        cont=0;
        for(j=0;j<pow(2,N);j++)
        {
            cont+=prob[i][j];
        }
        if(cont != pow(2,N))
            printf("\tERROR EN EL PASO %d\n", i);
    }

    FILE* fracnest;     //  Definimos y abrimos el archivo que va a almacenar la fracci�n de estados visitados.
    fracnest=fopen("fracnest_REGLA.dat", "w");

    if (fracnest == NULL)   //  Bucle para verificar la apertura del archivo exitosa.
    {
        printf("No se ha podido abrir 'fracnest_REGLA.dat' para escritura. Saliendo...\n");
        exit(1);
    }

    for(i=0;i<T+1;i++)  //  Bucle para escribir en el archivo los datos obtenidos en cada paso.
    {
        nest=0;     //  Inicializaci�n de la variable que almacena los estados visitados en cada paso.
        for(j=0;j<pow(2,N);j++)     //  Bucle que cuenta los estados visitados.
        {
            if(prob[i][j]!=0)
                nest++;
        }
        fracc=nest/pow(2, N);       //  C�lculo de la fracci�n de estados visitados.
        fprintf(fracnest, " %d\t%f\n", i, fracc);   //  Almacenamiento del valor anterior en el archivo.
    }
    fclose(fracnest);       //  Orden para cerrar el archivo una vez escrito.

    return 0;
}
