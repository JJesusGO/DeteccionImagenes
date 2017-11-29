#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
#include <string>
#include <ctime>
#include <cctype>


class Seed{

    unsigned int seedi;
    std::string  seeds;

 public:

    Seed();
    Seed(std::string palabra);
    Seed(const unsigned int n);

    private:

    void CrearSeed(const std::string palabra);

    public:

    const inline int GetSeedValor() const {return seedi;}
    const inline std::string GetSeedString() const {return seeds;}

};
class Random{

    static Seed seed;

    public:

    static void SetRandom();
    static void SetRandomSeed();
    static void SetSeed(const Seed &s);

    static int Next();
    static int Next(int mn,int mx);
    static int Next(int mx);

    static double NextBoolean();

    static double NextDouble();
    static double NextDouble(double mn,double mx);
    static double NextDouble(double mx);

    static inline Seed& GetSeed(){return seed;}

};




#endif
