#ifndef FLAGHEADDEF 
#define FLAGHEADDEF

#include <string>
#include <ctime>
class Flags{
    public: 
        Flags();
        void printParam();
        // define length and width of the lattice
        int length;
        int width;
        int N = length * width;
        // define temperature, if use sequential 
        double T;
        double Tmin, Tmax, Tint;
        // define thermalization step and total simulation step
        int thermalization;
        int nsteps;
        // define sample interval and flag indicate whether output 
        // data (lattice state and statistical data)
        int sample_inter;
        bool is_output;
        std::string lattice_file;
        // flag indicating sequential simulation
        bool is_sequential;
        bool Tmax_2_Tmin;
        // simulation methods:
        std::string sim_meth;

    private:
        std::string author = "Zhaocheng Liu";
        std::string time_of_finish = "July 28, 2017";
};

#endif 