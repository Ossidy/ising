#include<unordered_map> 
#include<random> 
#include<vector> 
#include<iostream>

#include "Lattice.h"

typedef std::unordered_map<int, std::vector<int>> hashMap;

Lattice::Lattice(Flags Params){
    // random seed
    srand(static_cast <unsigned> (time(0)));

    // init parameters
    length = Params.length;
    width = Params.width;
    N = Params.N;

    // create and initialize lattice
    lattice = new int [N];
    initLattice();

    // create and initialize nbrs
    hashMap nbrs;
    initNbrs();

    // initialize obeservable arrays in the sequence of:
    // pure magnetization, abs of magnetization, sqr of magnetization and energy
    obs_statis = new double [4];
}

Lattice::~Lattice(){
    // destructor
    delete[] lattice;
    delete[] obs_statis;
}

void Lattice::initLattice(){
    // int lattice[N];
    for (int i = 0; i < N; i++){
        int rand_num = rand() % 2;
        // std::cout<<int((double(rand_num) - 0.5) *2)<<" ";
        lattice[i] = int((double(rand_num) - 0.5) *2);
    }
    // return lattice;
}

void Lattice::initNbrs(){

    for (int i = 0; i < N; i++){
        // in the seqence of left, right, up to down
        // from python to c++: n % M -> (n % M + M) % M: different for negative number
        std::vector<int> vec(4);
        vec[0] = (i / length) * length + ((i - 1) % length + length) % length;
        vec[1] = (i / length) * length + ((i + 1) % length + length) % length;
        vec[2] = ((i - width) % N + N) % N - (length - width);
        vec[3] = ((i + width) % N + N) % N + (length - width);
        vec[2] = (vec[2] % N + N) % N;
        vec[3] = (vec[3] % N + N) % N;
        nbrs[i] = vec;
    }
    return;
}

double Lattice::getMagnetization(){
    int mag = 0;
    for (int i = 0; i < N; i++){
        mag += lattice[i];
    }
    return double(mag) / N;
}

double Lattice::getEnergy(){
    int eng = 0;
    for (int i = 0; i < N; i++){
        std::vector<int> nbr;
        nbr = nbrs[i];
        double e;
        e = -1 * lattice[i] * (lattice[nbr[0]] + lattice[nbr[1]] +
                               lattice[nbr[2]] + lattice[nbr[3]]);
        eng += e;
    }
    return eng / double(N) / 2.0;
}

void Lattice::printVector(const std::vector<int>& vector){
    for (auto it = vector.begin(); it != vector.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void Lattice::printLattice(){
    for (int i = 0; i <N; i++){
        if (i % length == 0 && i != 0){
            std::cout << "\n";
        }
        if (lattice[i] > 0){
            std::cout << "\t" << "+" << lattice[i];
        }
        else{
            std::cout << "\t" << lattice[i];
        }
    }
    std::cout << "\n";
}

void Lattice::printNbrs(){
    for (auto it = nbrs.cbegin(); it != nbrs.cend(); it++){
        std::cout << (*it).first << ":" << "\t";
        printVector((*it).second);
    }
}