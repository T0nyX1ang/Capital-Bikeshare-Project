set terminal pdf
set output "./datedata/datedata-2014.png"
set style data histogram
set style histogram clustered gap 0.05
set style fill solid 0.9 border
set title "Date count in 2014"
set xrange [0: 1440]
set xlabel "Date"
set ylabel "Count"
plot "./datedata/datedata-2014.dat" using 2 title ""