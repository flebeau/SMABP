#!/usr/bin/gnuplot

reset

if (!exists("input_file")) input_file='results.dat'
if (!exists("output_file")) output_file='plots.pdf'

set terminal pdf
set output output_file

set key top left box 3
stats input_file nooutput
plot for [IDX=1:STATS_blocks] input_file index (IDX-1) u 1:2 w lines title columnhead