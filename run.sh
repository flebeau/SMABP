#!/bin/bash

mkdir -p build
cd build
cmake ..
make -j
cd ..
for BANDITS in bandits/*.mab
do
	bandits_name=$(basename "$BANDITS" .mab)
	build/SMABP -N 50 -I 100000 -B "$BANDITS" --naive --vanishing -e 0.8 0.5 0.2 0.1 0.05 > "results/${bandits_name}.dat"
	#build/SMABP -N 100 -I 100000 -B "$BANDITS" -e 0.1 --vanishing > "results/${bandits_name}.dat"
done
cd results
gnuplot plot.plt
#gnuplot -e "output_file='plots2.pdf'" plot.plt
if [ -x "$(command -v evince)" ]; then
    evince plots.pdf
	#evince plots2.pdf
fi
