#include "Random.h"

Seed Random::seed;

/*SE ENCARGA DE ESTABLECER UNA SEED EN BASE AL TIEMPO*/
void Random::SetRandom(){
    srand(time(NULL));
}
/*REESTABLECE LA SEED QUE ESTE ALMACENADA EN LA CLASE*/
void Random::SetRandomSeed(){
    srand(seed.GetSeedValor());
}

/*FUNCION UTILIZADA PARA ESTABLECER CON QUE SEED SE DESEA QUE FUNCIONE LA CLASE RANDOM*/
void Random::SetSeed(const Seed &s){
    seed = s;
    SetRandomSeed();
}

/*GENERACION DE UN NUMERO ALEATORIO ENTRE 0 Y RAND_MAX*/
int Random::Next(){
    return rand();
}
/*GENERACION DE UN NUMERO ALEATORIO ENTRE UN MINIMO Y MAXIMO ESTABLECIDO*/
int Random::Next(int mn,int mx){
    return (mn + (rand() % (mx-mn+1)));
}
/*GENERACION DE UN NUMERO ALEATORIO ENTRE UN 0 Y UN MAXIMO ESTABLECIDO*/
int Random::Next(int mx){
   return Next(0,mx);
}
/*GENERACION DE UN NUMERO DOBLE ENTRE 0 Y 1*/
double Random::NextDouble(){
    return static_cast<double>(rand())/RAND_MAX;
}
/*GENERACION DE UN NUMERO DOBLE ENTRE UN MINIMO Y UN MAXIMO*/
double Random::NextDouble(double mn,double mx){
    return  NextDouble()*(mx-mn) + mn;
}
/*GENERACION DE UN NUMERO DOBLE ENTRE 0 Y UN MAXIMO*/
double Random::NextDouble(double mx){
    return NextDouble(0,mx);
}
/*CONSTRUCTOR POR DEFECTOR DE LA CLASE SEED*/
Seed::Seed(){
    this->seedi = 0;
    this->seeds = "DESCONOCIDA";
}
/*CONSTRUCTOR DE UN OBJETO SEED BASADA EN UNA SEED CADENA*/
Seed::Seed(const std::string palabra){
    CrearSeed(palabra);
}
/*CONSTRUCTOR DE UN OBJETO SEED BASADO EN CUANTOS CARACTERES SE DESEA QUE TENGA LA SEED CADENA*/
Seed::Seed(const unsigned int n){

   std::string palabra;
   int  caracter;

   //EN ESTA PARTE SE ENCARGA DE GENERAR UNA CADENA ALFANUMERICA DE N CARACTERES
   for(int i=0;i<n;i++){

        do{caracter = (int)('0')+(rand() % (int)'Z');}
        while( !(
                  ((caracter >= (int)'0') && (caracter <= (int)'9')) ||
                  ((caracter >= (int)'A') && (caracter <= (int)'Z'))
                 )
              );
        palabra += static_cast<char>(caracter);

   }
   CrearSeed(palabra);

}
/*BASADO EN UNA CADENA, SE PROCEDE A CREAR UNA SEED NUMERICA PARA LA UTILIZACION DE SRAND*/
void Seed::CrearSeed(std::string palabra){

    int resultado = 1;

    //LA SEED SE CREA GRACIAS A NUMERO DE LA TABLA ASCII Y SU POSICION EN LA CADENA MULTIPLICADA POR UN FACTOR CONTANTE
   for(int i=0;i<palabra.size();i++){
     if(isalpha(palabra[i]))
       palabra[i] = (char)toupper((int)palabra[i]);
       resultado += (int)(palabra[i])*12345*i;
   }

   this->seedi = resultado;
   this->seeds = palabra;

}



