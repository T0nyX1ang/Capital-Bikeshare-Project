set terminal png
set output "datedata-2015.png"
set style data histogram
set style histogram clustered gap 0.05
set style fill solid 0.9 border
set title "Date count in 2015"
set xrange [-5: 370]
set xlabel "Date"
set ylabel "Count"
plot "datedata-2015.dat" using 2 title ""