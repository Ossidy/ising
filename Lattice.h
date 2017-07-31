#ifndef LATTICEHEADEF
#define LATTICEHEADEF

#include<unordered_map> 
#include<random> 
#include<vector> 

#include "Flags.h"

typedef std::unordered_map<int, std::vector<int>> hashMap;

class Lattice{
    public:
        Lattice(Flags Params);
        ~Lattice();
        
        int* lattice;
        hashMap nbrs;
        double* obs_statis;

        double getMagnetization();
        double getEnergy();

        void printNbrs();
        void printLattice();
    
    private:
        int length, width;
        int N;

        void initLattice();
        void initNbrs();

        void printVector(const std::vector<int>& vector);
};













#endif