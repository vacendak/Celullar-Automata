#include <stdio.h>                      /*      Incluímos las librerías     */
#include <stdlib.h>                     /*      que necesitamos             */
#include <time.h>                       /*      para el funcionamiento      */
#include <locale.h>                     /*      del programa.               */

int main(int argc, char** argv)         //  Función principal del programa.
{
    setlocale(LC_CTYPE, "spanish");     //  Función para el uso de caracteres españoles.
    int a, b, c, i, N, n;               //  Declaración de variables.
    float r;

    printf("\n\t\t  ### GENERADOR DE NÚMEROS ALEATORIOS ENTEROS ###\n");            /************************************/
    printf("\n\t\t  ¿Cuántos números quieres generar?  ");                          /*  Funciones para presentar        */
    scanf(" %i", &N);                                                               /*  por pantalla los mensajes       */
                                                                                    /*  para pedir la entrada           */
    printf("\n\t\t Inroduce el intervalo, [a,b], donde quieres los números: \n");   /*  de los datos necesarios,        */
    printf("\n\t\t a = ");                                                          /*  y funciones para guardarlos en  */
    scanf(" %i", &a);                                                               /*  las variables que los           */
    printf("\t\t b = ");                                                            /*  van a almacenar.                */
    scanf(" %i", &b);                                                               /************************************/

    while (b<=a)           // Bucle que comprueba si los datos de intervalo introducidos son válidos.
    {
        printf("\n\t\t Ese valor no es válido, b tiene que ser mayor que a.\n");
        printf("\n\t\t Vuelve a introducir b: ");
        scanf(" %i", &b);
    }
    printf("\n");

    c = b - a;              // Cálculo de la anchura del intervalo.

    srand(time(0));         // Función que asigna como semilla el reloj de la CPU.
    for(i=1;i<N+1;i++)      // Bucle para generar los N números aleatorios pedidos.
    {
        r = (double)rand()/(RAND_MAX+1.0);  // Generación de un número aleatorio entre 0 y 1.
        n = r*(c+1)+a;                      // Expresión que sitúa al número anterior dentro del intervalo.


        printf("\t\t El %iº número entero aleatorio en el intervalo [%i,%i] es: %i\n", i, a, b, n);
    }
    printf("\n");
    system("pause");

    return 0;
}
