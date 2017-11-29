#pragma once

#ifndef PSO_H
#define PSO_H

#include <cstdio>
#include <cmath>
#include "Particula.h"

class PSO{

    int cantidad;
    int mejorparticula;
    int iteraciones;
    float *rmin,*rmax;
    int dimensiones;
    Particula *particulas;

    float (*evaluar)(Particula &particula);
    int (*actualizar)(Particula &particula);
    int (*seleccionar)(Particula &particula,Particula &mejor);

    public:
        PSO(int particulas,float *rmin,float *rmax,int dim,int iteraciones);
        ~PSO();

    private:

        void CrearEnjambre();
        void ForzarEnjambre();

    public:

        void MostrarEnjambre();
        void MostrarPSO();
        void MostrarPSO(FILE *file);
        void MostrarMejorParticula();
        void MostrarMejorParticula(FILE *file);

        void NextIteracion();

        void IniciarEnjambre(float c1,float c2,float vmin,float vmax);
        void MovimientoEnjambre();
        void EvaluarEnjambre();

        void ActualizarEnjambre();
        void SeleccionEnjambre();

    public:

        void SetFunciones(float (*evaluar)(Particula &particula),
                          int (*actualizar)(Particula &particula),
                          int (*seleccionar)(Particula &particula,Particula &mejor));

        const inline int GetCantidadParticulas() const {return cantidad;}
        const inline float GetRangoMinimo(int i) const {return rmin[i];}
        const inline float GetRangoMaximo(int i) const {return rmax[i];}
        const inline int GetDimensiones() const {return dimensiones;}
        const inline Particula& GetMejorParticula() const {return particulas[mejorparticula];}
        const inline int GetMejorParticulaIndex() const {return mejorparticula;}
        const inline Particula& GetParticula(int i) const {return particulas[i];}
        const inline int GetIteraciones() const {return iteraciones;}
        const inline float GetError(float valor) const {return valor - GetMejorParticula().GetFitnessP();}
        const inline float GetErrorAbs(float valor) const {return fabs(GetError(valor));}

        const inline bool IsNextIteracion(float valor,float error,int iteraciones) const {return (GetErrorAbs(valor) > error) && ((iteraciones) < GetIteraciones()); }

};




#endif

