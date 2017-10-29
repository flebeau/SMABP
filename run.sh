#!/bin/bash

mkdir -p build
cd build
cmake ..
make -j
cd ..
build/SMABP > results/results.dat
cd results
gnuplot plot.plt
evince plots.pdf
