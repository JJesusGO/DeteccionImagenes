#pragma once
#ifndef PSOMANAGER_H

#include <cstdio>
#include <conio.h>
#include <string>
#include "PSO.h"
#include "bitmap_image.hpp"

class PSOManager{

    PSO *pso;
    float error,valor;
    float erroractual;
    int n;
    float *porcentajes;

    public:

    PSOManager(PSO *pso,float valor,float error = -1);
    ~PSOManager();

	void Run();
	void GuardarImagen(int ancho,int largo,std::string archivo);
    void SetPorcentajes(float *porcentajes,int n);

};


#endif
