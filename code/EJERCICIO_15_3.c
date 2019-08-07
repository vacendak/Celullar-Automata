#include <stdio.h>                      /*      Inclu�mos las librer�as     */
#include <stdlib.h>                     /*      que necesitamos             */
#include <time.h>                       /*      para el funcionamiento      */
#include <locale.h>                     /*      del programa.               */

int main(int argc, char** argv)         //  Funci�n principal del programa.
{
    setlocale(LC_CTYPE, "spanish");     //  Funci�n para el uso de caracteres espa�oles.
    int a, b, c, i, N, n;               //  Declaraci�n de variables.
    float r;

    printf("\n\t\t  ### GENERADOR DE N�MEROS ALEATORIOS ENTEROS ###\n");            /************************************/
    printf("\n\t\t  �Cu�ntos n�meros quieres generar?  ");                          /*  Funciones para presentar        */
    scanf(" %i", &N);                                                               /*  por pantalla los mensajes       */
                                                                                    /*  para pedir la entrada           */
    printf("\n\t\t Inroduce el intervalo, [a,b], donde quieres los n�meros: \n");   /*  de los datos necesarios,        */
    printf("\n\t\t a = ");                                                          /*  y funciones para guardarlos en  */
    scanf(" %i", &a);                                                               /*  las variables que los           */
    printf("\t\t b = ");                                                            /*  van a almacenar.                */
    scanf(" %i", &b);                                                               /************************************/

    while (b<=a)           // Bucle que comprueba si los datos de intervalo introducidos son v�lidos.
    {
        printf("\n\t\t Ese valor no es v�lido, b tiene que ser mayor que a.\n");
        printf("\n\t\t Vuelve a introducir b: ");
        scanf(" %i", &b);
    }
    printf("\n");

    c = b - a;              // C�lculo de la anchura del intervalo.

    srand(time(0));         // Funci�n que asigna como semilla el reloj de la CPU.
    for(i=1;i<N+1;i++)      // Bucle para generar los N n�meros aleatorios pedidos.
    {
        r = (double)rand()/(RAND_MAX+1.0);  // Generaci�n de un n�mero aleatorio entre 0 y 1.
        n = r*(c+1)+a;                      // Expresi�n que sit�a al n�mero anterior dentro del intervalo.


        printf("\t\t El %i� n�mero entero aleatorio en el intervalo [%i,%i] es: %i\n", i, a, b, n);
    }
    printf("\n");
    system("pause");

    return 0;
}
