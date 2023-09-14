set datafile separator ","
set terminal svg size 1280,720 font'arial, 22'
set output "out.svg"
set lmargin 20 
set rmargin 10 
set size 1,1
set xdata time
set timefmt '%H:%M:%S'
set ylabel 'Temprature / Humidity' offset -4
set y2label 'CO2[ppm]'
set yrange [0:100]
set y2range [0:1600]
set y2tics
set ytics ('5°C 20%%' 20,'10°C 40%%' 40,'15°C 60%%' 60,'20°C 80%%' 80,'25°C 100%%' 100,) nomirror
set xtics format '%H:%M'
filename = "input.csv"
plot filename using 1:($2*4) with line axis x1y1 title 'Temp',filename using 1:3 with line axis x1y1 lc 'blue' title 'Humi',filename using 1:4 with line axis x1y2 lc 'green' title 'CO2'
exit
