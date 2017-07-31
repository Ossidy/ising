Flags.o : Flags.cpp Flags.h
		g++ -std=c++11 -c -O3 Flags.cpp 

Lattice.o : Lattice.cpp Lattice.h Flags.h
		g++ -std=c++11 -c -O3 Lattice.cpp

Sampler.o : Sampler.cpp Sampler.h Lattice.h Flags.h
		g++ -std=c++11 -c -O3 Sampler.cpp

ising.o : ising.cpp Flags.h Lattice.h
		g++ -std=c++11 -c -O3 ising.cpp 

ising : Flags.o ising.o Lattice.o Sampler.o
		g++ -std=c++11 -o ising Flags.o ising.o Lattice.o Sampler.o