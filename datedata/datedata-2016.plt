set terminal png
set output "datedata-2016.png"
set style data histogram
set style histogram clustered gap 0.05
set style fill solid 0.9 border
set title "Date count in 2016"
set xrange [-5: 370]
set xlabel "Date"
set ylabel "Count"
plot "datedata-2016.dat" using 2 title ""