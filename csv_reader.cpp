// CSV reader for data...

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct time_type
{
	int year[8];
	int month[12];
	int date[31];
	int hour[24];
	int minute[60];
	int countable_date[12 * 31];
	int countable_time[1440];
} time_data[8];

void tokenize_time(string str, int relv_year)
{
	char* end;
	int place = 0;
	int month_place = str.find('/');
	string month = str.substr(place, month_place - place);
	int date_place = str.find('/', month_place + 1);
	string date = str.substr(month_place + 1, date_place - month_place - 1);
	int year_place = str.find(' ', date_place + 1);
	string year = str.substr(date_place + 1, year_place - date_place - 1);
	int hour_place = str.find(':', year_place + 1);
	string hour = str.substr(year_place + 1, hour_place - year_place - 1);
	int minute_place = str.find(',', hour_place + 1);
	string minute = str.substr(hour_place + 1, hour_place - minute_place - 1);
	time_data[relv_year].month[stoi(month) - 1]++;
	time_data[relv_year].date[stoi(date) - 1]++;
	time_data[relv_year].year[stoi(year) - 2010]++;
	time_data[relv_year].hour[stoi(hour)]++;
	time_data[relv_year].minute[stoi(minute)]++;
	time_data[relv_year].countable_date[(stoi(month) - 1) * 31 + stoi(date) - 1]++;
	time_data[relv_year].countable_time[stoi(hour) * 60 + stoi(minute)]++;
}

bool validate_date(int month, int date) 
{
	switch (month) {
	case 2:
		if (date <= 28)
			return true;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (date < 31)
			return true;
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return true;
		break;
	}
	return false;
}

void data(int year) 
{
	string yearstr = to_string(year);
	ofstream time_file("./timedata/timedata-" + yearstr + ".dat");
	time_file<<"time count"<<endl;
	for (int i = 0; i < 1440; i++)
		time_file<<i<<" "<<time_data[year - 2010].countable_time[i]<<endl;
	time_file.close();

	ofstream date_file("./datedata/datedata-" + yearstr + ".dat");
	int datecount = 1;
	date_file<<"date count"<<endl;
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 31; j++)
			if (time_data[year - 2010].countable_date[i * 31 + j] != 0 || validate_date(i + 1, j + 1)) 
			{
				date_file<<datecount<<" "<<time_data[year - 2010].countable_date[i * 31 + j]<<endl;
				datecount++;
			}
	date_file.close();
}

void format(string &s)
{
	char* end;
	int dashtime = s.find('-');
	if (dashtime != -1) {
		int backdashtime = s.find('-', dashtime + 1);
		int space = s.find(' ', backdashtime + 1);
		string year = s.substr(0, dashtime);
		string month = s.substr(dashtime + 1, backdashtime - dashtime - 1);
		string date = s.substr(backdashtime + 1, space - backdashtime - 1);
		string time = s.substr(space + 1, -1);
		s = month + "/" + date + "/" + year + " " + time;
	}
}

void plot_utils(int year)
{
	// create gnuplot needed files
	string yearstr = to_string(year);
	ofstream time_plot("./timedata/timedata-" + yearstr + ".plt");
	time_plot<<"set terminal png"<<endl<<
			   "set output \"timedata-" + yearstr + ".png\""<<endl<<
			   "set style data histogram"<<endl<<
			   "set style histogram clustered gap 0.05"<<endl<<
			   "set style fill solid 0.9 border"<<endl<<
		       "set title \"Time count in " + yearstr + "\""<<endl<<
			   "set xrange [0: 1440]"<<endl<<
			   "set xlabel \"Time\""<<endl<<
			   "set ylabel \"Count\""<<endl<<
			   "plot \"timedata-" + yearstr + ".dat\" using 2 title \"\"";
	time_plot.close();
	ofstream date_plot("./datedata/datedata-" + yearstr + ".plt");
	date_plot<<"set terminal png"<<endl<<
			   "set output \"datedata-" + yearstr + ".png\""<<endl<<
			   "set style data histogram"<<endl<<
			   "set style histogram clustered gap 0.05"<<endl<<
			   "set style fill solid 0.9 border"<<endl<<
		       "set title \"Date count in " + yearstr + "\""<<endl<<
			   "set xrange [-5: 370]"<<endl<<
			   "set xlabel \"Date\""<<endl<<
			   "set ylabel \"Count\""<<endl<<
			   "plot \"datedata-" + yearstr + ".dat\" using 2 title \"\"";
	date_plot.close();
}

int main()
{
	system("mkdir datedata");
	system("mkdir timedata");
	string filename[8][5] = 
	{
		{
			"2010-Q4-cabi-trip-history-data.csv"
		},
		{ 
			"2011-Q1-cabi-trip-history-data.csv", 
		  	"2011-Q2-cabi-trip-history-data.csv", 
		  	"2011-Q3-cabi-trip-history-data.csv",  
		  	"2011-Q4-cabi-trip-history-data.csv"
		},
		{ 	
			"2012-Q1-cabi-trip-history-data.csv", 
			"2012-Q2-cabi-trip-history-data.csv", 
		  	"2012-Q3-cabi-trip-history-data.csv",  
		  	"2012-Q4-cabi-trip-history-data.csv"
		},
		{ 
			"2013-Q1-cabi-trip-history-data.csv", 
		  	"2013-Q2-cabi-trip-history-data.csv", 
		  	"2013-Q3-cabi-trip-history-data.csv",  
		  	"2013-Q4-cabi-trip-history-data.csv"
		},
		{ 
			"2014-Q1-cabi-trip-history-data.csv", 
		  	"2014-Q2-cabi-trip-history-data.csv", 
		  	"2014-Q3-cabi-trip-history-data.csv",  
		  	"2014-Q4-cabi-trip-history-data.csv"
		},
		{ 	
			"2015-Q1-Trips-History-Data.csv", 
		  	"2015-Q2-Trips-History-Data.csv", 
		  	"2015-Q3-cabi-trip-history-data.csv",  
		  	"2015-Q4-Trips-History-Data.csv"
		},
		{ 
			"2016-Q1-Trips-History-Data.csv", 
		  	"2016-Q2-Trips-History-Data.csv", 
		  	"2016-Q3-Trips-History-Data-1.csv", 
		  	"2016-Q3-Trips-History-Data-2.csv", 
		  	"2016-Q4-Trips-History-Data.csv"
		},
		{ 
			"2017-Q1-Trips-History-Data.csv",
		}
	};
	for (int i = 0; i <= 7; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (filename[i][j] != "") 
			{
				ifstream fin(filename[i][j]);
				string line;
				int count = 0;
				while (getline(fin, line))
				{   
					int start = line.find(',');
					if (count == 0) {
						count++;
						continue;
					}
					start++;
					int stop = start;
					while (line[stop] != ',')
						stop++;
					string split = line.substr(start, stop - start);
					// format split string
					format(split);
					// cout<<split<<endl;
					tokenize_time(split, i);
					count++;
				}				
			}
		}
		data(i + 2010);	
		plot_utils(i + 2010);
	}
	return 0;
}