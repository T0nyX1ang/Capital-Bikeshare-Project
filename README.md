# Capital-Bikeshare-Project
This is a repository for our university training project.

Here are the main features we offer.

## entry-counter
Simply counts data entries in a file. Deprecated soon.

## season-fitting
Fitting total entries based on season. You need to have MatLab to use it.

## CSV-reader
A simple reader for CSV-format data. In this project, a time praser is implemented to convert common time format(MM/DD/YYYY HH:MM) to computer recognizable format(365 days, 1440 minutes array). Then a summary dataset is created.

The usage is:
```shell
  g++ csv-reader.cpp -o csv-reader
  (chmod +x csv-reader)
  ./csv-reader
```
It will generate all 'GNUplot' files needed.

## Plot
Data visualization module to show the data more friendly. We make it automatically by a bash shell.
```shell
  chmod +x plotting.sh
  ./plotting.sh
```

It will generate PNG files.

## MapParser
Creating a mapping between dock no. and geographical coordinates.

The usage is:
```shell
  python3 MapParser.py
```

## Efficiency
* About 1.8s to process about 3000000 data entries on a Linux distro.
* About 13s to process about 20000000 data entries on a Linux distro.

## Notices:
* Linux distro is needed.(untested on Windows or WSL)
* Open source data can be fetched on Capital Bikeshare's website.
