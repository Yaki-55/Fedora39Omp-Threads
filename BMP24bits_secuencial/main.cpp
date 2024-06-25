#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>    
#include "BMP.h"

double timeval_diff(struct timeval* a, struct timeval* b) {
	return	(double)(a->tv_sec + (double)a->tv_usec / 1000000) -
		(double)(b->tv_sec + (double)b->tv_usec / 1000000);
}

int main(int argc, char** argv) {
	// Verificar que se haya pasado la dirección de la imagen como argumento 
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <ruta_a_la_imagen>" << std::endl;
        return 1;
    }

    // Obtener la dirección de la imagen desde los argumentos de la línea de comandos
    const char* imagePath = argv[1];

    struct timeval t_ini, t_fin;
    double secs;

    // Crear el objeto BMP usando la dirección de la imagen proporcionada
    BMP bmp(imagePath);
	//	bmp.printHeader();
	//	bmp.blueChannel();

	gettimeofday(&t_ini, NULL);

	bmp.fromRGBtoGRAY();

	gettimeofday(&t_fin, NULL);

	secs = timeval_diff(&t_fin, &t_ini);
	printf("%.10g\n", secs * 1000.0);
	bmp.save("grises.bmp");

	//    getchar();  // Con esta l�nea evitaremos que se cierre la consola
	return 0;
}
