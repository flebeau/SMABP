#!/bin/bash

mkdir -p build
cd build
cmake ..
make -j
cd ..
for BANDITS in bandits/*.mab
do
	bandits_name=$(basename "$BANDITS" .mab)
	build/SMABP -N 50 -I 10000 -B "$BANDITS" -e 0.05 0.1 0.2 0.5 0.8 > "results/${bandits_name}.dat"
done
cd results
for DATA in *.dat
do
	DATA_NAME=$(basename "$DATA" .dat)
	gnuplot -e "input_file='$DATA'" -e "output_file='${DATA_NAME}.pdf'" plot.plt
done
if [ -x "$(command -v evince)" ]; then
    evince *.pdf
fi
