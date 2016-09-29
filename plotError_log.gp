set title 'compute-pi'
set xlabel 'N'
set ylabel 'Error Rate'
set logscale y 10
set style fill solid
set datafile separator ","
plot csvFile using 1:2 title 'baseline' with linespoints, \
     csvFile using 1:3 title 'openmp 2 thread' with linespoints, \
     csvFile using 1:4 title 'openmp 4 thread' with linespoints
