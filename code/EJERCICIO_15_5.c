#include <stdio.h>          //  Incluímos las librerías necesarias para el programa.
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>


#define REGLA 182           //  Regla para los ACEs.
#define N 1000              //  Número de caldas de los ACEs.
#define T 500               //  Número de pasos de evolución.


int main(int argc, char *argv[])    //  DECLARACIÓN DE LA FUNCIÓN PRINCIPAL.
{
    int i,j,nv1,nv2,n;                  /* ZONA DE DECLARACIÓN DE VARIABLES */
    int ACE1[T+1][N+2];                 /*    PARA LA GENERACIÓN DE LOS     */
    int ACE2[T+1][N+2];                 /*   DOS ACEs, Y PARA EL CÁLCULO    */
    long int dist=0;                    /*    DE LA DISTANCIA DE HAMMING.   */

    setlocale(LC_CTYPE, "spanish"); //  Comando para usar caracteres epañoles.
    int npts, m;                        /************************************/
    double x, y;                        /*            ZONA DE               */
    double Sx, Sy, Sxy, Sxx, Syy;       /*          DECLARACIÓN             */
    double pend, y0;                    /*          DE VARIABLES            */
    double m_x;                         /*        DE LA REGRESIÓN.          */
    double r2;                          /************************************/

    srand(time(0));     //  SEMILLA INICIAL DE LA FUNCIÓN RAND REFERIDA AL RELOJ DE LA CPU.

    for(i=0;i<T+1;i++)  //  BUCLE PARA LA INICIALIZACIÓN DE LA REJILLA DE LOS DOS ACEs.
        {
        for(j=0;j<N+2;j++);
            {
                ACE1[i][j]=ACE2[i][j]=0;
            }
        }

    for(n=0;n<N+2;n++)  //  BUCLE PARA LA GENERACIÓN ALEATORIA DE LOS ELEMENTOS DE LA PRIMERA LÍNEA.
        {
            ACE1[0][n]=ACE2[0][n]=(((double)rand())/((RAND_MAX)+1.0)<0.5);  //  La primera fila aleatoria
        }                                                                   //  e igual para los dos ACEs.

        ACE2[0][N/2]=!ACE1[0][N/2]; //  CAMBIO DEL VALOR DEL ELEMENTO CENTRAL DE LA PRIMERA LÍNEA DEL ACE2.

    FILE* hamm;                         //  GENERACIÓN Y APERTURA DEL ARCHIVO PARA ESCRITURA.
    hamm = fopen("hamming.dat", "w");   //  DE LAS DISTANCIAS DE HAMMING ENTRE ACE1 Y ACE2.
    if (hamm == NULL)                   //  CONDICIÓN PARA VERIFICAR QUE LA ACCIÓN ANTERIOR HA SIDO EXITOSA.
    {
        printf("No se ha podido abrir hamming.dat para escritura. Saliendo...\n");
        exit(1);
    }

    for(i=1;i<T+1;i++)      //  INICIO DEL BUCLE PARA LA GENERACIÓN DE LOS DOS ACE: ACE1 Y ACE2.
    {
        dist=0;             //  INICIALIZACIÓN DE LA VARIABLE QUE GUARDA LA DISTANCIA DE HAMMING.
        for(j=1;j<N+1;j++)
        {
            nv1=(ACE1[i-1][j+1]|ACE1[i-1][j]<<1|ACE1[i-1][j-1]<<2);     //  Generación del ACE1.
            ACE1[i][j]=(REGLA>>nv1)&1;
            nv2=(ACE2[i-1][j+1]|ACE2[i-1][j]<<1|ACE2[i-1][j-1]<<2);     //  Generación del ACE2.
            ACE2[i][j]=(REGLA>>nv2)&1;

            dist+=ACE1[i][j]^ACE2[i][j]; // CONTADOR DE LAS DISTANCIAS MEDIANTE EL OPERADOR XOR.
        }
        fprintf(hamm, " %d\t%ld\n", i, dist);   //  GUARDADO DE LAS DISTANCIAS EN EL ARCHIVO 'hamming.dat'.

        ACE1[i][0]=ACE1[i][N];          // ACTUALIZACIÓN DE LAS CONDICIONES PERIÓDICAS DE CONTORNO.
        ACE1[i][N+1]=ACE1[i][1];
        ACE2[i][0]=ACE2[i][N];
        ACE2[i][N+1]=ACE2[i][1];

    }
    fclose(hamm);   //  CERRADO DEL ARCHIVO 'hamming.dat' PARA ESCRITURA.

    hamm=fopen("hamming.dat", "r");         //  Comandos para abrir archivo para lectura.

    if (hamm == NULL)                       //  Condición de control de apertura del archivo exitosa.
    {
        printf("No se ha podido abrir hamming.dat para lectura. Saliendo...\n");
        exit(1);
    }

    npts=0;         /****************************/
    Sx=0.0;         /*  ZONA DE INICIALIZACIÓN  */
    Sy=0.0;         /*     DE LAS VARIABLES     */
    Sxy=0.0;        /*     PARA EL CÁLCULO      */
    Sxx=0.0;        /*     DE LA REGRESIÓN.     */
    Syy=0.0;        /****************************/

    do
    {
        m=fscanf(hamm, " %lf%lf", &x, &y);      //  Comando de lectura del archivo 'hamming.dat'.
        if (m==2)                           /************************************/
        {                                   /*                                  */
            npts++;                         /*          BUCLE DE CÁLCULO,       */
            Sx+=log(x);                     /*      CON LOS VALORES LEÍDOS      */
            Sy+=log(y);                     /*          EN EL ARCHIVO,          */
            Sxy+=log(x)*log(y);             /*      PARA LAS FÓRMULAR DE        */
            Sxx+=log(x)*log(x);             /*          REGRESIÓN.              */
            Syy+=log(y)*log(y);             /*                                  */
        }                                   /************************************/
    }while (m==2);

    fclose(hamm);         //  Comando que vuelve a cerrar el archivo de datos leído.

    pend=(npts*Sxy-Sx*Sy)/(npts*Sxx-Sx*Sx); /************************************/
    y0=(Sy-pend*Sx)/npts;                   /*         ZONA DE CÁLCULO          */
                                            /*         DE LAS VARIABLES         */
    m_x=(npts*Sxy-Sx*Sy)/(npts*Syy-Sy*Sy);  /*         DE LA REGRESIÓN.         */
                                            /*                                  */
    r2=m_x*pend;                            /************************************/

                                                                /************************************/
    printf("\n\tRESULTADO DE LA REGRESIÓN:\n");                 /*                                  */
    printf("\n\tEcuación Genérica: ");                          /*           ZONA DE                */
    printf(" log Ht = alpha * log t + Y0 \n");                  /*                                  */
                                                                /*         PRESENTACIÓN             */
    printf("\n\talpha (exponente de Hamming) = %g\n", pend);    /*                                  */
                                                                /*         DE RESULTADOS            */
    printf("\n\tY0 (ordenada en el origen) = %g\n", y0);        /*                                  */
                                                                /*         DE LA REGRESIÓN.         */
    printf("\n\tCoeficiente de correlación r^2 = %g\n", r2);    /*                                  */
    printf("\n\n");                                             /************************************/

    system("pause");

    return 0;
}
