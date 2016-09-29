set title 'compute-pi'
set xlabel 'N'
set ylabel 'Time(sec)'
set style fill solid 0.5
set datafile separator ","
plot csvFile using 1:2 title 'baseline' with linespoints, \
     csvFile using 1:3 title 'openmp 2 thread' with linespoints, \
     csvFile using 1:4 title 'openmp 4 thread' with linespoints
