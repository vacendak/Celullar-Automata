#ifndef _LIBGUARDAIMAGEN_H_     /*Librer�a con las declaraciones de las funciones*/
#define _LIBGUARDAIMAGEN_H_     /*          que guardan las im�genes.            */

#include <stdio.h>

void guardaPGMi(char* nombre, int anchura, int altura,
                int* pixels, int pixel_min, int pixel_max);
void guardaPGMd(char* nombre, int anchura, int altura,
                int* pixels, int pixel_min, int pixel_max);

#endif
