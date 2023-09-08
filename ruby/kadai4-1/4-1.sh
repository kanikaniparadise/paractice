#!/bin/sh
gnuplot << EOF
set ylabel '角度[deg]'
set xlabel '[0-1]'
set datafile separator ","
set terminal svg size 1280,720 font'arial, 22'
set output "4-1.svg"
set xrange [0:1]
set yrange [0:180]
set sample 20
plot 180*x
exit
E0F
