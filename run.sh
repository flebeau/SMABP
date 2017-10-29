#!/bin/bash

mkdir -p build
cd build
cmake ..
make -j
cd ..
build/SMABP -N 50 -I 10000 -B test -e 0.1 0.2 0.5 0.8 0.01 > results/results.dat
cd results
gnuplot plot.plt
evince plots.pdf
