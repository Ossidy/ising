#ifndef SAMPLERHEADEF
#define SAMPLERHEADER

#include<unordered_map>
#include<unordered_set> 
#include<random>
#include<vector> 

#include "Flags.h"
#include "Lattice.h"

typedef std::unordered_map<int, std::vector<int>> hashMap;

class Sampler{
    public:
        Sampler();
        Sampler(int seed);
        ~Sampler();

        void clusterSampling(int* lattice, hashMap nbrs, double* statis, Flags Params, bool is_print=true);
        void MetropolisSampling(int* lattice, hashMap nbrs, double* statis, Flags Params, bool is_print=true);

        void testRandom();
    private:
        // std::random_device rd;
        std::mt19937 gen;
        // std::uniform_real_distribution<> dis_real;
        // std::uniform_int_distribution<> dis_int;

        double getMagnetization(int* lattice, int N);
        double getEnergy(int* lattice, hashMap nbrs, int N);
};



#endif