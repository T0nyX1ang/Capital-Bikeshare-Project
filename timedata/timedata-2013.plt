set terminal png
set output "timedata-2013.png"
set style data histogram
set style histogram clustered gap 0.05
set style fill solid 0.9 border
set title "Time count in 2013"
set xrange [0: 1440]
set xlabel "Time"
set ylabel "Count"
plot "timedata-2013.dat" using 2 title ""