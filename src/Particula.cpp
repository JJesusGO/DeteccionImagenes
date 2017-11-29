#include "Particula.h"

//Constructor- Parte donde incializamos todas la variables(parametros)  de la particula en cero o nulo
Particula::Particula()
{
	Xi = NULL;
	Pi = NULL;
	Vi = NULL;

	C1 = 0;
	C2 = 0;

	Vmax = 0;
	Vmin = 0;

	FitnessP = 0;
	FitnessX = 0;

	Dim = 0;
}
//Destructor-Liberacion de memoria
Particula::~Particula()
{
	delete[] Xi;
	delete[] Pi;
	delete[] Vi;
}
void Particula::IniciarParticula(float c1, float c2, float vmin, float vmax,int dim)
{
	//Inicializacion de variables con los informacion  que se recibe desde el PSO
	//Constantes del PSO
	C1 = c1;
	C2 = c2;
	//Velocidades
	Vmax = vmax;
	Vmin = vmin;
	//mejores posciones
	FitnessX = 0;
	FitnessP = 0;
	//Dimension
	Dim = dim;

	//Asignacion de memoria
	Xi = new float[dim];
	Pi = new float[dim];
	Vi = new float[dim];

	//Inicializacion de los parametros principales de la particula
	for (unsigned int i = 0;i < dim;i++)
	{
		Xi[i] = 0;
		Pi[i] = 0;
		Vi[i] = 0;
	}
}
void Particula::SetPosicion(int i, float valor)
{
	//Almacena la posicion que da el PSO dentro de la variable Xi de la particula
	Xi[i] = valor;
}
void Particula::SetPosicion(int i, float pmin, float pmax)
{
	//Funcion que crea la posicion de la particula aleatoriamente solo recibiendo el rnago desde el PSO
    float aleatorio = Random::NextDouble(pmin, pmax);
	Xi[i] = aleatorio;
}
void Particula::SetMejorPosicion(int i, float valor)
{
	//Almacena la mejor posicion de la particula
	Pi[i] = valor;
}
void Particula::ActualizarVelocidad(Particula &Particula)
{
	//Obtencion de la velicidad
	float Y1, Y2;
	for (unsigned int d = 0;d < Dim;d++)
	{
		Y1 = Random::NextDouble();
		Y2 = Random::NextDouble();
		Vi[d] += C1*Y1*(Pi[d] - Xi[d]) + C2*Y2*(Particula.Pi[d] - Xi[d]);
		if (Vi[d] > Vmax){
			 Vi[d] = Vmax;
		}
		if (Vi[d] < Vmin){
			 Vi[d] = Vmin;
		}

		//MOVIMIENTO SIMPLE
		if (fabs(Vi[d]) < 1 && fabs(Vi[d]) > 0)
			Vi[d] /= fabs(Vi[d]);
		else
			Vi[d] = roundf(Vi[d]);

	}
}
void Particula::ActualizarPosicion(void)
{
	//Suma la velocidad a la poscion para asi tener una nueva posicion
	for (unsigned int d = 0;d < Dim;d++)
	{
		Xi[d] += Vi[d];
	}
}
void Particula::SetFitnessX(float valor)
{
	FitnessX = valor;
}
void Particula::SetFitnessP(float valor)
{
	FitnessP = valor;
}
const void Particula::MostrarParticula(int n) const
{
	//Funcion que muestra la informacion de la particula
	printf("C1[%i] = %+2.4f", n, C1);
	printf("\nC2[%i] = %+2.4f", n, C2);
	printf("\nFX[%i] = %+f", n, FitnessX);
	printf("\nFP[%i] = %+f", n, FitnessP);
	printf("\n\nX[%i]: ",n);
	for (int d = 0; d < Dim;d++)
		printf("%+2.4f ", Xi[d]);
	printf("\nV[%i]: ", n);
	for (int d = 0; d < Dim;d++)
		printf("%+2.4f ", Vi[d]);
	printf("\nP[%i]: ", n);
	for (int d = 0; d < Dim;d++)
		printf("%+2.4f ", Pi[d]);
}
const void Particula::MostrarParticula(int n,FILE *file) const
{
	//Funcion que imprime la infmacion d ela particula en un archivo de texto
	fprintf(file,"C1[%i] = %+2.4f", n, C1);
	fprintf(file,"\nC2[%i] = %+2.4f", n, C2);
	fprintf(file,"\nFX[%i] = %+f", n, FitnessX);
	fprintf(file,"\nFP[%i] = %+f", n, FitnessP);
	fprintf(file,"\n\nX[%i]: ",n);
	for (int d = 0; d < Dim;d++)
		fprintf(file,"%+2.4f ", Xi[d]);
	fprintf(file,"\nV[%i]: ", n);
	for (int d = 0; d < Dim;d++)
		fprintf(file,"%+2.4f ", Vi[d]);
	fprintf(file,"\nP[%i]: ", n);
	for (int d = 0; d < Dim;d++)
		fprintf(file,"%+2.4f ", Pi[d]);
}


