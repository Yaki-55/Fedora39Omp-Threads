/*
Cargar y procesar imágenes BMP de 24bits con C++
http://www.widget-101.com/
Autor: Christiam Mena
*/
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>    
#include "BMP.h"

void* hilograyscale(void* param);

double timeval_diff(struct timeval* a, struct timeval* b)
{
    return	(double)(a->tv_sec + (double)a->tv_usec / 1000000) -
        (double)(b->tv_sec + (double)b->tv_usec / 1000000);
}

int main(int argc, char** argv) {
    struct timeval t_ini, t_fin;
    double secs;
    BMP bmp("nature.bmp");

    gettimeofday(&t_ini, NULL);

    pthread_t h_hilograyscale;
    pthread_create(&h_hilograyscale, NULL, hilograyscale, &bmp);

    pthread_join(h_hilograyscale, NULL);

    gettimeofday(&t_fin, NULL);

    secs = timeval_diff(&t_fin, &t_ini);
    printf("%.10g\n", secs * 1000.0);

    bmp.save("grises.bmp");

    return 0;
}


void* hilograyscale(void* param) {
    BMP* bmp = (BMP*)param;
    bmp->fromRGBtoGRAY();
    return NULL;
}

