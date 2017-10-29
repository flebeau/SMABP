#!/bin/bash

mkdir -p build
cd build
cmake ..
make -j
cd ..
for BANDITS in bandits/*.mab
do
	bandits_name=$(basename "$BANDITS" .mab)
	build/SMABP -N 50 -I 10000 -B "$BANDITS" -e 0.8 0.5 0.2 0.1 0.05 > "results/${bandits_name}.dat"
done
cd results
gnuplot plot.plt
if [ -x "$(command -v evince)" ]; then
    evince plots.pdf
fi
