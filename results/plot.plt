#!/usr/bin/gnuplot

reset

if (!exists("output_file")) output_file='plots.pdf'

set terminal pdf
set output output_file

set xlabel "Number of steps"
set ylabel "Mean regret"
set key top left box 3
set key font ",10"

files = system("ls -1 *.dat")
do for [file in files] {
   command = "basename ".file." .dat"
   name = system(command)
   stats file nooutput
   set title name
   plot for [IDX=1:STATS_blocks] file index (IDX-1) u 1:2 w lines title columnhead
}