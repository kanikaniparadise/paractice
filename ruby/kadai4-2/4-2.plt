set ylabel '角度[deg]'
set xlabel '[0-1]'
set terminal svg size 1280,720 font'arial, 22'
set xrange [0:1]
set yrange [0:180]
set sample 20
set output "4-2-1.svg"
plot "4-2-1.txt" with linespoint
set output "4-2-2.svg"
plot "4-2-2.txt" with linespoint
exit
