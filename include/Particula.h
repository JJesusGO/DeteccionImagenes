#pragma once

#include <cstdlib>
#include <cstdio>;
#include "Random.h"

class Particula
{
public:
	//Contructor y destructor 
	Particula();
	~Particula();
public:
	//Funciones que reciben y regresaran informacion sobre la particula
	void IniciarParticula(float c1, float c2, float vmin, float vmax, int dim);
	void ActualizarPosicion(void);
	void SetPosicion(int i,float valor);
	void SetPosicion(int i,float pmin,float pmax);
	void SetMejorPosicion(int i,float valor);
	void ActualizarVelocidad(Particula &particula);
	void SetFitnessX(float valor);
	void SetFitnessP(float valor);
	const void MostrarParticula(int n) const;
	const void MostrarParticula(int n,FILE *file) const;

	//Funciones que regresan informacion sobre los parametros  de la particula
	const inline float GetVelocidad(int i) const { return Vi[i]; }
	const inline float GetVelocidadMinima() const { return Vmin; }
	const inline float GetVelocidadMaxima() const { return Vmax; }
	const inline float GetPosicion(int i) const { return Xi[i]; }
	const inline int   GetDimensiones() const { return Dim; }
	const inline float GetMejorPosicion(int i) const { return Pi[i]; }
	const inline float GetFitnessX() const { return FitnessX; }
	const inline float GetFitnessP() const { return FitnessP; }

    private:
	//Variables que almacenan informacion sobre las parametros de la particula

	//dimensiones
	int   Dim;
	//PArametros Posicion,Mejor Posicion, Velocidad
	float *Xi;
	float *Pi;
	float *Vi;
	//Constantes de la formula de velocidad del PSO
	float  C1, C2;
	//Velocidad maxima y velicdad minima
	float  Vmax, Vmin;
	//Mejor Psocion de la particula 
	float  FitnessX, FitnessP;

};

