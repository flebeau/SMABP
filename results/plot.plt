#!/usr/bin/gnuplot

reset

set terminal pdf
set output "plots.pdf"

set key top left box 3
datafile = 'results.dat'
stats datafile
plot for [IDX=1:STATS_blocks] datafile index (IDX-1) u 1:2 w lines title columnhead