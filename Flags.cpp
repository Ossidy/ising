#include "Flags.h"
#include <iostream>
// #include <string>
// #include <ctime>

// constructor
Flags::Flags(){
    // state configuration
    length = 8;
    width = 8;
    N = length * width;
    // Temperatrue
    T = 2.26;
    Tmin = 0.5;
    Tmax = 5;
    Tint = 0.1;
    // steps
    thermalization = 4300;
    nsteps = 10000;
    // sample rate
    sample_inter = 50;
    is_output = true;
    lattice_file = "./notforuse.dat";
    // sequential simulation
    is_sequential = false;
    Tmax_2_Tmin = true;
    // simulation method
    sim_meth = "clustering";
}

void Flags::printParam(){
    // show information of the parameters
    std::cout << "******************************************************************" << std::endl;
    std::cout << "Simulation of Ising Model" << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Date: " << time_of_finish << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << "Basic parameters are shown below: " << std::endl;
    std::cout << "length of model: " << "\t" << length << std::endl;
    std::cout << "width of model: " << "\t" << width << std::endl;
    std::cout << "total num of spins: " << "\t" << N << std::endl;
    std::cout << "simulation methods: " << "\t" << sim_meth << std::endl;
    std::cout << "thermalization times: " << "\t" << thermalization << std::endl;
    std::cout << "sampling times: " << "\t" << nsteps << std::endl;
    std::cout << "******************************************************************" << std::endl;
    if (is_sequential == false){
        std::cout << "Doing one-time temperature simulation" << std::endl;
        if (is_output == true){
            std::cout << "Output lattice configuration as array at each" << sample_inter << " steps" << std::endl;
            std::cout << "File will be saved in: " << lattice_file <<std::endl;
        }
        else{
            std::cout << "Notice! Simulation file will not be saved, please make sure set properly!!!" << std::endl;
        } 
    }
    else{
        if (Tmax_2_Tmin == false){
            std::cout << "Doing continuous temperatrue simulation from " << Tmin << " to " << Tmax << " with interval of " << Tint << std::endl;
        } 
        else{
            std::cout << "Doing continuous temperatrue simulation from " << Tmax << " to " << Tmin << " with interval of " << Tint << std::endl;
        }
    }
    std::cout << "******************************************************************" << std::endl;
}