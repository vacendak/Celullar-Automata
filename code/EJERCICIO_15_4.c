#include <stdio.h>          //  Inclu�mos las librer�as necesarias para el programa.
#include <stdlib.h>
#include <time.h>


#define REGLA 90            //  Regla para los ACEs.
#define N 1000              //  N�mero de caldas de los ACEs.
#define T 500               //  N�mero de pasos de evoluci�n.


int main(int argc, char *argv[])    //  DECLARACI�N DE LA FUNCI�N PRINCIPAL.
{
    int i,j,nv1,nv2,n;          /* ZONA DE DECLARACI�N DE VARIABLES */
    int ACE1[T+1][N+2];         /*    PARA LA GENERACI�N DE LOS     */
    int ACE2[T+1][N+2];         /*   DOS ACEs, Y PARA EL C�LCULO    */
    long int dist=0;            /*    DE LA DISTANCIA DE HAMMING.   */

    srand(time(0));         //  SEMILLA INICIAL DE LA FUNCI�N RAND REFERIDA AL RELOJ DE LA CPU.

    for(i=0;i<T+1;i++)      //  BUCLE PARA LA INICIALIZACI�N DE LA REJILLA DE LOS DOS AC
        {
        for(j=0;j<N+2;j++);
            {
                ACE1[i][j]=ACE2[i][j]=0;
            }
        }

    for(n=0;n<N+2;n++)      //  BUCLE PARA LA GENERACI�N ALEATORIA DE LOS ELEMENTOS DE LA PRIMERA L�NEA.
        {
            ACE1[0][n]=ACE2[0][n]=(((double)rand())/((RAND_MAX)+1.0)<0.5);  //  PRIMER PASO ALEATORIO E IGUAL.
        }

        ACE2[0][N/2]=!ACE1[0][N/2];     //  CAMBIO DEL VALOR DEL ELEMENTO CENTRAL DE LA PRIMERA L�NEA DEL ACE2.

    FILE* hamm;                         //  GENERACI�N Y APERTURA DEL ARCHIVO PARA ESCRITURA
    hamm = fopen("hamming.dat", "w");   //  DE LAS DISTANCIAS DE HAMMING ENTRE ACE1 Y ACE2.
    if (hamm == NULL)       //  CONDICI�N PARA VERIFICAR QUE LA ACCI�N ANTERIOR HA SIDO EXITOSA.
    {
        printf("No se ha podido abrir hamming.dat para escritura. Saliendo...\n");
        exit(1);
    }

    for(i=1;i<T+1;i++)          //  INICIO DEL BUCLE PARA LA GENERACI�N DE LOS DOS ACE: ACE1 Y ACE2
    {
        dist=0;                 //  INICIALIZACI�N DE LA VARIABLE QUE GUARDA LA DISTANCIA DE HAMMING.
        for(j=1;j<N+1;j++)
        {
            nv1=(ACE1[i-1][j+1]|ACE1[i-1][j]<<1|ACE1[i-1][j-1]<<2);     //  Generaci�n del ACE1.
            ACE1[i][j]=(REGLA>>nv1)&1;
            nv2=(ACE2[i-1][j+1]|ACE2[i-1][j]<<1|ACE2[i-1][j-1]<<2);     //  Generaci�n del ACE2.
            ACE2[i][j]=(REGLA>>nv2)&1;

            dist+=ACE1[i][j]^ACE2[i][j];    // CONTADOR DE LAS DISTANCIAS MEDIANTE EL OPERADOR XOR.
        }
        fprintf(hamm, " %d\t%ld\n", i, dist);    //  GUARDADO DE LAS DISTANCIAS EN EL ARCHIVO 'hamming.dat'.

        ACE1[i][0]=ACE1[i][N];          // ACTUALIZACI�N DE LAS CONDICIONES PERI�DICAS DE CONTORNO.
        ACE1[i][N+1]=ACE1[i][1];
        ACE2[i][0]=ACE2[i][N];
        ACE2[i][N+1]=ACE2[i][1];

    }
    fclose(hamm);       //  CERRADO DEL ARCHIVO 'hamming.dat' PARA ESCRITURA.

    return 0;
}
