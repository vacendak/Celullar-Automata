#ifndef _LIBGUARDAIMAGEN_H_     /*Librería con las declaraciones de las funciones*/
#define _LIBGUARDAIMAGEN_H_     /*          que guardan las imágenes.            */

#include <stdio.h>

void guardaPGMi(char* nombre, int anchura, int altura,
                int* pixels, int pixel_min, int pixel_max);
void guardaPGMd(char* nombre, int anchura, int altura,
                int* pixels, int pixel_min, int pixel_max);

#endif
