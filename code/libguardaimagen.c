#include <stdio.h>

/*  Programa con las definiciones de las funciones que guardan la imagen generada del ACE.
    Contiene las funciones guardaPGMi y guardaPGMd, aunque para este ACE sólo se usa
    la primera.*/

void guardaPGMi(char* nombre, int anchura, int altura, int *pixels,
                int pixel_min, int pixel_max)
{
    int i,j,ij,p;   //Declaración de variables.
    FILE* imagen;   //Archivo imagen.

    imagen=fopen(nombre,"wb");  //Se abre el archivo imagen para escritura en bits.
    fprintf(imagen,"P2");
    fprintf(imagen,"#guardaPGMi %s\n",nombre);
    fprintf(imagen,"%d %d\n",anchura,altura);
    fprintf(imagen,"255\n");

    ij=0;           //Bucle que guarda los puntos en la imagen en el archivo.
    for(i=0;i<altura;i++)
    {
        for(j=0;j<anchura;j++)
        {
            p=(255*(pixels[ij]-pixel_min))/(pixel_max-pixel_min);
            if(p<0)p=0;
            if(p>255)p=255;

            fprintf(imagen," %d",p);

            ij++;
        }
        fprintf(imagen,"\n");
    }
    fclose(imagen); //Cierre del archivo imagen.

    return;
}
void guardaPGMd(char* nombre, int anchura,int altura,double *pixels,
                double pixel_min,double pixel_max)
{
    int i,j,ij,p;
    FILE* imagen;

    imagen=fopen(nombre,"wb");
    fprintf(imagen,"P2");
    fprintf(imagen,"#guardaPGMd %s\n",nombre);
    fprintf(imagen,"%d %d\n",anchura,altura);
    fprintf(imagen,"255\n");

    ij=0;
    for(i=0;i<altura;i++)
    {
        for(j=0;j<anchura;j++)
        {
            p=(int)(255*(pixels[ij]-pixel_min))/(pixel_max-pixel_min);
            if(p<0)p=0;
            if(p>255)p=255;

            fprintf(imagen," %d",p);

            ij++;
        }
        fprintf(imagen,"\n");
    }
    fclose(imagen);

    return;
}
