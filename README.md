SMABP
====

SMABP is a small simulation program implementing the Stochastic Multi-Armed Bandit problem with a specification file format for the system. It also implements various greedy strategies:

  * naive greedy;
  * &epsilon;-greedy;
  * vanishing greedy.

Prerequisites
-------------
* CMake >= 3.1
* Boost: timer and program_options
* C++ compiler with C++11 standard
* Gnuplot >= 4.6
* OpenMP (recommended)

Compiling and launching examples
--------------------------------
You can use the given script in the root directory 

        ./run.sh

Otherwise the program can be compiled directly using cmake:  

        mkdir -p build
        cd build/
        cmake ..
        make -j

Program Usage
-------------
See the help command: 

        build/SMABP --help

System specification file format
--------------------------------
Each line of the file corresponds to a bandit. For now there are only two types of bandits:

1. Deterministic with value v: `D v`
2. Uniform with mean m and minimum value l: `U m l`
