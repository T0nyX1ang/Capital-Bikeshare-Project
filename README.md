# Capital-Bikeshare-Project
This is a repository for our university training project.

To create the summary using datasets, you need to change something in the program, and run this:
```
g++ csv_reader.cpp -o csv_reader
./csv_reader
```

You will need GNUplot(greater than version 5.00) to plot the figures. The syntax is:
```
gnuplot --persist timeplot.plt
gnuplot --persist dateplot.plt
```

## CSV-reader
A simple reader for CSV-format data. In this project, a time praser is implemented to convert common time format(MM/DD/YYYY HH:MM) to computer recognizable format(365 days, 1440 minutes array). Then a summary dataset is created.

## Plot
Data visualization module to show the data more friendly.

## Efficiency
About 1.8s to process about 3000000 data entries on a Linux distro.
