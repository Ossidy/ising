#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <ctime>
#include <random>
#include <algorithm>
#include <iterator>

#include "Flags.h"
#include "Lattice.h"
#include "Sampler.h"

void probe();

int main(int argc, char* argv[]){
    std::cout << "Simulation start!!!";
    std::cout << "\n";

    Flags Params;
    // double T; // temperature
    // int nsteps;
    if (1 < argc){Params.T = atof(argv[1]);}
    if (2 < argc){Params.nsteps = atoi(argv[2]);}
    if (3 < argc){Params.thermalization = atoi(argv[3]);}

    // print all parameters
    Params.printParam();

    // test Lattice.cpp
    Lattice model(Params);
    // model.printLattice();
    // model.printNbrs();

    Sampler sampler(-1);
    // sampler.testRandom();
    // sampler.clusterSampling(model.lattice, model.nbrs, model.obs_statis, Params.T, Params.thermalization, Params);    
    sampler.sequentialSampling(Params.sim_meth, model.lattice, model.nbrs, model.seq_statis, Params);
    model.export_seq_statis();

    return 0;
}


void probe(){
    std::cout << "I'm here!" << "\n";
}

