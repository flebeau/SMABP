#!/usr/bin/gnuplot

reset

if (!exists("input_file")) exit
if (!exists("output_file")) exit

set terminal pdf
set output output_file

set xlabel "Number of steps"
set ylabel "Mean regret"
set key top left box 3
set key font ",10"
stats input_file nooutput
plot for [IDX=1:STATS_blocks] input_file index (IDX-1) u 1:2 w lines title columnhead
