#include<unordered_map>
#include<unordered_set>
#include<random> 
#include<vector> 
#include<iostream>
#include<fstream>

#include "Flags.h"
#include "Lattice.h"
#include "Sampler.h"

typedef std::unordered_map<int, std::vector<int>> hashMap;


Sampler::Sampler(int seed){
    
    // initialize random generator
    if(seed <= 0){
        gen.seed((std::random_device())());
        std::cout << "Random generator with seed from random_device()" << std::endl;
    }
    else{
        gen.seed(seed);
        std::cout << "Random generator initialized with seed: " << seed << "." << std::endl;
    }
}

Sampler::~Sampler(){
    std::cout << "Finished" << std::endl;
}


double Sampler::getMagnetization(int* lattice, int N){
    int mag = 0;
    for (int i = 0; i < N; i++){
        mag += lattice[i];
    }
    return double(mag) / N;
}

double Sampler::getEnergy(int* lattice, hashMap nbrs,  int N){
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


void Sampler::MetropolisSampling(int* lattice, hashMap nbrs, double* statis, Flags Params, bool is_print){
    // do Markove sampling by simple Metropolis-Hasting algorithms
    // arguments:
    //      T: temperature in unit of Kelvin degree
    //      lattice: array stores the spin state (either -1 or +1)
    //      N: number of total spins
    //      nbrs: a map (dictionary) recording the neighbour of each lattice position
    //      nsteps: number of sampling time

    double T = Params.T;
    int N = Params.N;
    int nsteps = Params.nsteps;
    int thermalization = Params.thermalization;
    std::ofstream LATTICE;
    // probe();
    LATTICE.open(Params.lattice_file);

    double beta = 1.0 / T;
    double mag_tot = 0;
    double mag_abs_tot = 0;
    double mag_sqr_tot = 0;
    double eng_tot = 0;
    int sample_time = 0;

    std::uniform_real_distribution<> dis_real(0, 1);
    std::uniform_int_distribution<> dis_int(0, N - 1);

    int remaining_steps = nsteps + thermalization;
    while (remaining_steps){
        // random choose a particle
        int k = dis_int(gen);
        int sumed_spins = 0;
        for (auto it = nbrs[k].begin(); it != nbrs[k].end(); it++){
            sumed_spins += lattice[*it];
        }

        double delta_energy = 2.0 * lattice[k] * sumed_spins;

        if (dis_real(gen) < exp(-beta * delta_energy)){
            lattice[k] *= -1;
        }
        // std::cout << getMagnetization(lattice, N) << std::endl;

        // if pass the thermalization, sample the result at each N simulation interval 
        if (remaining_steps <= nsteps && remaining_steps % N == 0){
            double mag_cur = getMagnetization(lattice, N);
            double eng_cur = getEnergy(lattice, nbrs, N);
            mag_tot += (mag_cur);
            mag_abs_tot += fabs(mag_cur);
            mag_sqr_tot += mag_cur * mag_cur;
            sample_time += 1;
            // std::cout << i << "\t" << fabs(mag_cur) << "\t" << eng_cur << std::endl;
            // std::cout << sample_time << std::endl;
        }

        remaining_steps--;
    }
    // record statistics
    statis[0] = mag_tot / sample_time;
    statis[1] = mag_abs_tot / sample_time;
    statis[2] = mag_sqr_tot / sample_time;
    // statis[3] = 
    // std::cout << sample_time << std::endl;
}

void Sampler::clusterSampling(int* lattice, hashMap nbrs, double* statis, Flags Params, bool is_print){
    // do cluster update sampling
    // arguments:
    //      T: temperature in unit of Kelvin degree
    //      lattice: array stores the spin state (either -1 or +1)
    //      nbrs: a map (dictionary) recording the neighbour of each lattice position
    //      statis: array for recording simulation results
    //      Params: class of Flags indicating all simulation parameters 

    // parse parameters from Flags Params to clear code
    double T = Params.T;
    int N = Params.N;
    int nsteps = Params.nsteps;
    int thermalization = Params.thermalization;
    std::ofstream LATTICE;
    // probe();
    LATTICE.open(Params.lattice_file);

    // define statistical parameters 
    double mag_tot = 0;
    double mag_abs_tot = 0;
    double mag_sqr_tot = 0;
    double eng_tot = 0;
    int sample_time = 0;
    
    // Wolff algorithm probability
    double p = 1.0 - exp(-2.0 / Params.T);

    // define random generator
    std::uniform_real_distribution<> dis_real(0, 1);
    std::uniform_int_distribution<> dis_int(0, N - 1);

    // if temperature greater than critical T, increase the sampling time for accuracy
    if (T > 3){
        nsteps = (8.5 * T - 22.5) * nsteps;
    }

    // start sampling
    for (int i = 0; i < nsteps + thermalization + 1; i++){
        // get random generator
        int k = dis_int(gen);

        // initialize pokect and cluster
        std::unordered_set<int> pocket, cluster;
        pocket.insert(k);
        cluster.insert(k);

        // update clusters
        while(pocket.size() != 0){
            // get random number within size of pocket [0, pocket.size())
            int sp = rand() % pocket.size();

            // advance to the random k-element and get the spin number [0, N)
            auto it_rsp = pocket.begin();
            std::advance(it_rsp, sp); 
            int rand_spin = *it_rsp;

            // get neighbor information as form of vector
            std::vector<int> nbr = nbrs[*it_rsp];

            // update
            for (auto it = nbr.begin(); it != nbr.end(); it++){
                if (lattice[*it] == lattice[rand_spin] && dis_real(gen) < p && (cluster.find(*it) == cluster.end())){
                    pocket.insert(*it);
                    cluster.insert(*it);
                }
            }
            pocket.erase(it_rsp);
        }

        // flip
        for (auto it = cluster.begin(); it != cluster.end(); it++){
            lattice[*it] *= -1;
        }

        // show thermalization...
        if (is_print == true && i % 500 == 0 && i < thermalization){
            std::cout << "thermalization finished: " << i << "/" << thermalization << std:: endl; 
        }

        // if pass the thermalization, sample the ising model with sample interval of N
        if (i > thermalization && i % Params.sample_inter == 0){
            double mag_cur = getMagnetization(lattice, N);
            double eng_cur = getEnergy(lattice, nbrs, N);
            mag_tot += (mag_cur);
            mag_abs_tot += fabs(mag_cur);            
            mag_sqr_tot += mag_cur * mag_cur;
            eng_tot += eng_cur;
            sample_time += 1;
            if (is_print){
                std::cout << "sampling: " << i - thermalization << "\t" << fabs(mag_cur) << "\t" << eng_cur << std::endl;
            }
            // output sample file if possible
            if (Params.is_output){
                LATTICE << T << " " << mag_cur << " " << fabs(mag_cur) << " " << mag_cur*mag_cur << " " << eng_cur << " ";
                for (int j = 0; j < N - 1; j++){
                    LATTICE << lattice[j] << " ";
                }
                LATTICE << lattice[N-1] << "\n";
            }
        }
    }
    // record statistics
    statis[0] = mag_tot / sample_time;
    statis[1] = mag_abs_tot / sample_time;
    statis[2] = mag_sqr_tot / sample_time;
    statis[3] = eng_tot / sample_time;
    // std::cout << sample_time << std::endl;
}

void Sampler::testRandom(){
    std::uniform_int_distribution<> dis_int(0, 10);
    for(int i = 0; i < 100; i++){
        std::cout << dis_int(gen) << " ";
    }
    std::cout << std::endl;
}