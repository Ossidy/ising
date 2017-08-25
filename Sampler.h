#ifndef SAMPLERHEADEF
#define SAMPLERHEADER

#include<unordered_map>
#include<unordered_set> 
#include<random>
#include<vector> 
#include<string>

#include "Flags.h"
#include "Lattice.h"

typedef std::unordered_map<int, std::vector<int>> hashMap;

class Sampler{
    public:
        Sampler();
        Sampler(int seed);
        ~Sampler();

        void clusterSampling(int* lattice, hashMap nbrs, double* statis, double T, int thermalization, Flags Params, bool is_print=true);
        void MetropolisSampling(int* lattice, hashMap nbrs, double* statis, double T, int thermalization, Flags Params, bool is_print=true);

        void sequentialSampling(std::string method, int* lattice, hashMap nbrs, std::map<int, std::vector<double>>& seq_statis, Flags Params, bool is_print=false);

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