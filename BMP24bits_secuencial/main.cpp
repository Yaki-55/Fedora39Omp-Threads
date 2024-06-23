/*
Cargar y procesar imágenes BMP de 24bits con C++
http://www.widget-101.com/
Autor: Christiam Mena
*/
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>    
#include "BMP.h"

double timeval_diff(struct timeval* a, struct timeval* b)
{
	return	(double)(a->tv_sec + (double)a->tv_usec / 1000000) -
		(double)(b->tv_sec + (double)b->tv_usec / 1000000);
}

int main(int argc, char** argv)
{
	struct timeval t_ini, t_fin;
	double secs;
	BMP bmp("nature.bmp");
	//	bmp.printHeader();
	//	bmp.blueChannel();

	gettimeofday(&t_ini, NULL);

	bmp.fromRGBtoGRAY();

	gettimeofday(&t_fin, NULL);

	secs = timeval_diff(&t_fin, &t_ini);
	printf("%.10g\n", secs * 1000.0);
	bmp.save("grises.bmp");

	//    getchar();  // Con esta línea evitaremos que se cierre la consola
	return 0;
}
