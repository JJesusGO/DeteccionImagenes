#include "PSO.h"

/*CONTRUCTOR DE LA CLASE PSO, ENCARGADO DE LA INICIALIACION DE TODOS SUS COMPONENTES*/
PSO::PSO(int particulas,float *rmin,float *rmax,int dimensiones,int iteraciones){

    this->cantidad = particulas;
    this->dimensiones = dimensiones;
    this->iteraciones = iteraciones;

    this->rmin = new float[dimensiones];
    this->rmax = new float[dimensiones];

    //CREACION DE LOS VECTORES DE RANGOS PARA CADA DIMENSION
    for(unsigned int i=0;i<dimensiones;i++){
        this->rmin[i] = rmin[i];
        this->rmax[i] = rmax[i];
    }

    mejorparticula = 0;

    //LOS PUNTEROS A FUNCIONES SON INICIALIZADOS COMO NULOS
    evaluar     = NULL;
    actualizar  = NULL;
    seleccionar = NULL;

    CrearEnjambre();
}
/*DESTRUCTOR DE LA CLASE PSO, SE ENCARGA DE LIBERAR TODA LA MEMORIA DE SUS VECTORES*/
PSO::~PSO(){

    delete [] particulas;
    delete [] rmin;
    delete [] rmax;

}
/*EN ESTA FUNCION SE CREA EL ENJAMBRE DE PARTICULAS DEPENDIENDO DE LA CANTIDAD DESEADA*/
void PSO::CrearEnjambre(){
    particulas = new Particula[GetCantidadParticulas()];
}
/*EN ESTA FUNCION SE INICIALIZAN TODAS LAS PARTICULAS EN BASE A LAS CARACTERISTICAS QUE SE DESEAN QUE TENGA*/
void PSO::IniciarEnjambre(float c1,float c2,float vmin,float vmax){
    for(unsigned int i=0;i<GetCantidadParticulas();i++){
            //INICIALIZACION DE CADA PARTICULA
        particulas[i].IniciarParticula(c1,c2,vmin,vmax,GetDimensiones());
            //POSICION INICIAL ALEATORIA
        for(unsigned int j=0;j<GetDimensiones();j++)
            particulas[i].SetPosicion(j,GetRangoMinimo(j),GetRangoMaximo(j));

    }
 //PRIMERA EJECUCION DE TODAS LAS FUNCIONES NECESARIAS PARA EL FUNCIONAMIENTO DE PSO
    EvaluarEnjambre();
    ForzarEnjambre();
    SeleccionEnjambre();
}
 /*EVALUACION DEL ENJAMBRE EN BASE A FUNCION EXTERNA*/
void PSO::EvaluarEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++)
        particulas[i].SetFitnessX(evaluar(particulas[i]));
}
/*ACTUALIZACION DE UN ENJAMBRE, BUSQUEDA DE LA MEJOR POSICION*/
void PSO::ActualizarEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++)
        if(actualizar(particulas[i])){
            particulas[i].SetFitnessP(particulas[i].GetFitnessX());
            for(unsigned int j=0;j<GetDimensiones();j++)
                particulas[i].SetMejorPosicion(j,particulas[i].GetPosicion(j));
        }

}
/*CON ESTA FUNCION, SE BUSCA FORZAR QUE LA POSICION ACTUAL ES LA MEJOR*/
void PSO::ForzarEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++){
            particulas[i].SetFitnessP(particulas[i].GetFitnessX());
            for(unsigned int j=0;j<GetDimensiones();j++)
                particulas[i].SetMejorPosicion(j,particulas[i].GetPosicion(j));
    }
}
/*ESTA FUNCION, ES LA FUNCION ENCARGADA DE LA BUSQUEDA DE LA MEJOR PARTICULA DEL ENJAMBRE DE MANERA EXTERNA*/
void PSO::SeleccionEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++)
        if(seleccionar(particulas[i],particulas[mejorparticula]))
            mejorparticula = i;
}
/*FUNCION ENCARGADA DE APLICAR TODO EL CALCULO DE VELOCIDADES Y MOVIMIENTO DE LA PARTICULA*/
void PSO::MovimientoEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++){
        particulas[i].ActualizarVelocidad(particulas[mejorparticula]);
        particulas[i].ActualizarPosicion();
    }
}
/*ESTA FUNCION SE ENCARGA DE GENERAR LA SIGUIENTE ITERACION*/
void PSO::NextIteracion(){

    MovimientoEnjambre();
    EvaluarEnjambre();
    ActualizarEnjambre();
    SeleccionEnjambre();

}
/*MUESTRA LA FICHA DE LA PSO*/
void PSO::MostrarPSO(){
    printf("PARTICULAS : %d\n",GetCantidadParticulas());
    printf("DIMENSIONES : %d\n",GetDimensiones());
    printf("ITERACIONES : %d\n",GetIteraciones());
    printf("MEJOR PARTICULA : \n\n");
    MostrarMejorParticula();
}
/*MUESTRA LA FICHA DE LA PSO EN UN ARCHIVO*/
void PSO::MostrarPSO(FILE *file){
    fprintf(file,"PARTICULAS : %d\n",GetCantidadParticulas());
    fprintf(file,"DIMENSIONES : %d\n",GetDimensiones());
    fprintf(file,"ITERACIONES : %d\n",GetIteraciones());
    fprintf(file,"MEJOR PARTICULA : \n\n");
    MostrarMejorParticula(file);
}
/*MUESTRA LA INFORMACION DE TODAS LAS PARTICULAS DEL ENJAMBRE*/
void PSO::MostrarEnjambre(){
    for(unsigned int i=0;i<GetCantidadParticulas();i++){
        particulas[i].MostrarParticula(i);
        printf("\n\n");
    }
}
/*MUESTRA LA INFORMACION DE LA MEJOR PARTICULA DEL ENJAMBRE*/
void PSO::MostrarMejorParticula(){
    GetMejorParticula().MostrarParticula(GetMejorParticulaIndex());
}
/*MUESTRA LA INFORMACION DE LA MEJOR PARTICULA DEL ENJAMBRE EN UN ARCHIVO*/
void PSO::MostrarMejorParticula(FILE *file){
    GetMejorParticula().MostrarParticula(GetMejorParticulaIndex(),file);
}
/*FUNCION ENCARGADA DE ESTABLECER LOS PUNTEROS A FUNCIONES PARA LA EVALUACION,ACTUALIZACION Y SELECCION*/
void PSO::SetFunciones(float (*evaluar)(Particula &particula),
                          int (*actualizar)(Particula &particula),
                          int (*seleccionar)(Particula &particula,Particula &mejor)){

    this->evaluar = evaluar;
    this->actualizar = actualizar;
    this->seleccionar = seleccionar;

}
