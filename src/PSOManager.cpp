#include "PSOManager.h"

/*CONTRUCTOR DE LA CLASSSE, PIDE LA REFERENCIA AL PSO QUE ADMINISTRARARA, EL VALOR DE FITNESS DESEADO Y EL ERROR DE CORTE*/
PSOManager::PSOManager(PSO *pso,float valor,float error){
    this->porcentajes = NULL;
    this->error = error;
    this->erroractual = 0;
    this->valor = valor;
    this->pso = pso;
    this->n = 0;
}
/*DESTRUCTOR ENCARGADO DE LIBERAR LA MEMORIA DEL VECTOR DE PORCENTAJES*/
PSOManager::~PSOManager(){
    if(this->porcentajes!=NULL)
        delete []this->porcentajes;
}
/*ESTA FUNCION ES LA ENCARGA DE COMENZAR LAS ITERACIONES DEL PSO*/
void PSOManager::Run(){

    //EN ESTA PARTE SE CONVIERTEN LOS PORCENTAJES DE EJECUCION EN LAS ITERACIONES REALES
    int *iteraciones = NULL;
    if(this->n!=0)
        iteraciones = new int[this->n];
    for(int i=0;i<n;i++)
        iteraciones[i] = static_cast<int>((porcentajes[i]/100)*(pso->GetIteraciones()));
    int t = 0;
    //ESTAS ITERACIONES SON AQUELLAS DONDE SE FORZARA LA IMPRESION DEL PSO
    printf("CALCULANDO...\n\n");

    //SECCION DE CREACION DE LOS ARCHIVOS DONDE SE GUARDARA TODOS LOS DATOS ARROJADOS POR EL ALGORITMO
    FILE *file = fopen("log.txt","w");
    FILE *data = fopen("data.txt","w");
    if(file){
        fprintf(file,"SEED: %s\n",Random::GetSeed().GetSeedString().c_str());
        pso->MostrarPSO(file);
        fprintf(file,"\n\n\n");
    }

    //WHILE PRINCIPAL, ESTE WHILE SE EJECUTARA SIEMPRE Y CUANDO FALTEN ITERACIONES O NO SE ALCANCE EL ERROR DESEADO
    while(pso->IsNextIteracion(valor,error,t)){
        pso->NextIteracion();
        bool impreso = false;
        for(int i=0;i<n;i++)
            if(t == iteraciones[i]){
                printf("-> %2.2f \% - (%i / %i)\n\n",porcentajes[i],t,pso->GetIteraciones());
                pso->MostrarMejorParticula();
                printf("\n\n");
                if(file){
                    fprintf(file,"-> %2.2f \% - (%i / %i)\n\n",porcentajes[i],t,pso->GetIteraciones());
                    pso->MostrarMejorParticula(file);
                    fprintf(file,"\n\n");
                }
                if(data)
                    fprintf(data,"%2.6e\t%d\n",pso->GetErrorAbs(valor),t);
                impreso = true;
            }
            //ESTE IF ES EL ENCARGADO DE EVALUAR DI A EXISTIDO UN CAMBIO EN EL ERROR PARA INFORMARLO EN EL ARCHIVO Y CONSOLA
            if(pso->GetErrorAbs(valor) != erroractual && !impreso){
                erroractual  = pso->GetErrorAbs(valor);
                printf("-> %2.2f \% - (%i / %i)\n\n",(float)t/pso->GetIteraciones()*100.0f,t,pso->GetIteraciones());
                pso->MostrarMejorParticula();
                printf("\n\n");
                if(file){
                    fprintf(file,"-> %2.2f \% - (%i / %i)\n\n",(float)t/pso->GetIteraciones()*100.0f,t,pso->GetIteraciones());
                    pso->MostrarMejorParticula(file);
                    fprintf(file,"\n\n");
                }
                if(data)
                    fprintf(data,"%2.6e\t%d\n",pso->GetErrorAbs(valor),t);
            }
        t++;
    }

    printf("-> 100.00 \% - (%i / %i)\n\n",pso->GetIteraciones(),pso->GetIteraciones());
    pso->MostrarMejorParticula();
    printf("\n");

    //CERRADO DEL ARCHIVOS
    if(file){
        fprintf(file,"-> 100.00 \% - (%i / %i)\n\n",pso->GetIteraciones(),pso->GetIteraciones());
        pso->MostrarMejorParticula(file);
        fprintf(file,"\n");
        fclose(file);
    }
    if(data){
        fprintf(data,"%2.6e\t%d\n",pso->GetErrorAbs(valor),t);
        fclose(data);
    }

}
void PSOManager::GuardarImagen(int ancho, int largo, std::string archivo) {

	bitmap_image imagen(ancho, largo);
	imagen.set_all_channels(255, 255, 255);

	image_drawer draw(imagen);
	draw.pen_width(1);
	draw.pen_color(0, 0, 0);

	for (int i = 0; i < pso->GetCantidadParticulas(); i++)
		draw.circle((int)pso->GetParticula(i).GetMejorPosicion(0),(int)pso->GetParticula(i).GetMejorPosicion(1), 1);
	

	imagen.save_image(archivo+"_particulas.bmp");

}

/*FUNCION ENCARGADA DE ESTABLECER EN QUE PORCENTAJES SE DESEA FORZAR LA SALIDA A CONSOLA DE INFORMACION DEL ALGORITMO*/
void PSOManager::SetPorcentajes(float *porcentajes,int n){
    //ESTE IF SOLO SE ENCARGA DE BORRAR LA INFORMACION ANTERIOR SI ES QUE EXISTIA
    if(this->porcentajes!=NULL)
        delete []this->porcentajes;
    this->porcentajes = new float[n];
    for(int i=0;i<n;i++)
        this->porcentajes[i] = porcentajes[i];
        this->n = n;
}
