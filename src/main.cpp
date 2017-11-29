#include <cstdio>
#include <cmath>
#include <string>

#include "Random.h"
#include "Particula.h"
#include "PSO.h"
#include "PSOManager.h"
#include "bitmap_image.hpp"

static bitmap_image *imagen = NULL,
					*bordes = NULL;


bool CargarImagen(std::string archivo) {

	imagen = new bitmap_image(archivo+".bmp");

	if (!(*imagen)) {
		printf("Error - Failed to open: imagen.bmp\n");
		return false;
	}


	const unsigned int height = imagen->height();
	const unsigned int width = imagen->width();
	const unsigned int n = height*width;

	float *dx = new float[height*width];
	float *dy = new float[height*width];

	bordes = new bitmap_image(width, height);

	for (int i = 0; i < n; i++) {
		dx[i] = 0;
		dy[i] = 0;
	}

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			rgb_t color;
			imagen->get_pixel(x, y, color);
			int k = (color.red + color.green + color.blue) / 3;
			imagen->set_pixel(x, y, k, k, k);
		}
	}

	for (int y = 0; y<height; y++)
		for (int x = 0; x < (width - 1); x++) {
			int k = y*width + x;
			rgb_t color1, color2;

			imagen->get_pixel(x, y, color1);
			imagen->get_pixel(x + 1, y, color2);

			dx[k] = color2.red - color1.red;
		}
	for (int y = 0; y < (height - 1); y++)
		for (int x = 0; x < width; x++) {
			int k = y*width + x;
			rgb_t color1, color2;

			imagen->get_pixel(x, y, color1);
			imagen->get_pixel(x, y + 1, color2);

			dy[k] = color2.red - color1.red;
		}
	for (int y = 0; y < (height - 1); y++)
		for (int x = 0; x < width; x++) {
			int k = y*width + x;
			char c = (char)sqrt(dx[k] * dx[k] + dy[k] * dy[k]);
			
			rgb_t color = { c, c, c };
			bordes->set_pixel(x, y, color);
		}

	imagen->save_image(archivo+"_grises.bmp");
	bordes->save_image(archivo+"_bordes.bmp");
	
	delete[]	dx;
	delete[]	dy;

	return true;

}
void MostrarTelon() {
	printf("\n\n--------------------------------------\n\n");
}

float Evaluar(Particula &particula) {

	
	int x = (int)particula.GetPosicion(0),
		y = (int)particula.GetPosicion(1);
	if (x < 0 || x >= (int)imagen->width() || y < 0 || y >= (int)imagen->height())
		return 0;

	rgb_t color;
	bordes->get_pixel(x, y, color);

	return color.red;
}
int Actualizar(Particula &particula) {
	if (particula.GetFitnessX() > particula.GetFitnessP())
		return 1;
	return 0;
}
int Seleccionar(Particula &particula,Particula &mejor) {
	if (particula.GetFitnessP() > mejor.GetFitnessP())
		return 1;
	return 0;
}

int main(int argc,char **argv) {

	Random::SetRandom();
	Random::SetSeed(Seed(6));
	std::string archivo = "imagen3";

	if (!CargarImagen(archivo))
		return -1;

	float	rmin[2] = {0.0f,0.0f},
			rmax[2] = { (float)imagen->width(),(float)imagen->height()};

	PSO pso(1000,rmin,rmax,2,10000);
	pso.SetFunciones(Evaluar, Actualizar, Seleccionar);
	pso.IniciarEnjambre(2, 1.5, -5,5);

	PSOManager manager(&pso, 255);
	manager.Run();
	manager.GuardarImagen(imagen->width(), imagen->height(), archivo);

		delete		imagen;
		delete		bordes;

		return 0;
	}

