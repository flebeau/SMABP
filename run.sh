#!/bin/bash

mkdir -p build
cd build
cmake ..
make -j
cd ..
for BANDITS in bandits/*.mab
do
	echo -n "### Treating system file $BANDITS ########################" | head -c 54
	bandits_name=$(basename "$BANDITS" .mab)
	#build/SMABP -N 400 -I 10000 -B "$BANDITS" --naive -e 0.8 0.5 0.2 0.1 0.05 --vanishing --ucb > "results/${bandits_name}.dat"
	build/SMABP -N 5000 -I 5000 -B "$BANDITS" -e 0.1 --vanishing --ucb > "results/${bandits_name}.dat"
done
cd results
#gnuplot plot.plt
gnuplot -e "output_file='plots6.pdf'" plot.plt
if [ -x "$(command -v evince)" ]; then
    #evince plots.pdf
	evince plots6.pdf
fi
