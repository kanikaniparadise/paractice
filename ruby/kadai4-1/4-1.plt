set ylabel '角度[deg]'
set xlabel '[0-1]'
set terminal svg size 1280,720 font'arial, 22'
set output "4-1.svg"
set xrange [0:1]
set yrange [0:180]
plot "output.txt" with linespoints 
exit
