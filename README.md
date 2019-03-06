# Capital-Bikeshare-Project
This is a repository for our university training project.

Here are the main features we offer.

## Basics:
### create_directory
Create directories needed.

### entry-counter
Simply counts data entries in a file. Deprecated soon.

### season-fitting
Fitting total entries based on season. You need to have MatLab to use it.

## CSV-reader
A simple reader for CSV-format data. In this project, a time praser is implemented to convert common time format(MM/DD/YYYY HH:MM) to computer recognizable format(365 days, 1440 minutes array). Then a summary dataset is created.

The usage is:
```shell
  g++ csv-reader.cpp -o csv-reader
  (chmod +x csv-reader)
  ./csv-reader
```
It will generate all 'Gnuplot' files needed.

## Generic Plot
Data visualization module to show the data more friendly. We make it automatically by a bash shell.
```shell
  chmod +x plotting.sh
  ./plotting.sh
```

## Weather Crawler
### Basic Version:
* Only generate data from 2014-2017, from a [Chinese weather provider](http://www.tianqihoubao.com/guoji/3195/).
* Data format are not very well.

### Pro Version:
* Well formated data by [Wunderground](https://www.wunderground.com/history/month/us/dc/washington/KDCA).
* Richer dataset, boarder classfication.

It will generate PNG files.

## Map Parser
Creating a mapping between dock no. and geographical coordinates.

The usage is:
```shell
  python3 MapParser.py
```

## Weather Regression Tool
### Stepwise regression yearly:
Doing stepwise regression from 2011-2016's weather data. Possible data modifications are:
* Linear process
* Quadartic process
* Cubic process
* Exponential process
* Logarithm process
* Fractional process

### Full regression:
Select nesserary data in stepwise process. Combine all the data together and verify the model using 2017's data.

## Efficiency
* About 1.8s to process about 3000000 data entries on a Linux distro.
* About 13s to process about 20000000 data entries on a Linux distro.

## Notices:
* Linux is needed.(untested on Windows or WSL)
* Open source data can be fetched on Capital Bikeshare's website.
