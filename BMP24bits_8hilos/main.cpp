#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>    
#include "BMP.h"

#define NUM_THREADS 8

void *hilograyscale(void *param);

double timeval_diff(struct timeval *a, struct timeval *b)
{
    return (double)(a->tv_sec + (double)a->tv_usec/1000000) -
           (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

int main(int argc, char** argv) {
    struct timeval t_ini, t_fin;
    double secs;
    BMP bmp ("nature.bmp");
    
    gettimeofday(&t_ini, NULL);
    
    pthread_t threads[NUM_THREADS]; // Array para almacenar los identificadores de los hilos

    // Creamos 8 hilos adicionales para procesamiento en paralelo
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, hilograyscale, &bmp);
    }
    
    // Esperamos a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    gettimeofday(&t_fin, NULL);
    
    secs = timeval_diff(&t_fin, &t_ini);
    printf("%.10g\n", secs * 1000.0);
    
    bmp.save("grises.bmp");
    
    return 0;
}

void *hilograyscale(void *param) {
    BMP *bmp = (BMP *)param;
    bmp->fromRGBtoGRAY();
    return NULL;
}
