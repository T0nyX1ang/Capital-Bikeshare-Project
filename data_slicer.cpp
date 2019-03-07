#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

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

void tokenize_time(string str, int &slice_year, int &slice_month, int &slice_day,
							   int &slice_hour, int &slice_minute)
{
	char* end;
	int place = 0;
	int month_place = str.find('/');
	string month = str.substr(place, month_place - place);
	int date_place = str.find('/', month_place + 1);
	string day = str.substr(month_place + 1, date_place - month_place - 1);
	int year_place = str.find(' ', date_place + 1);
	string year = str.substr(date_place + 1, year_place - date_place - 1);
	int hour_place = str.find(':', year_place + 1);
	string hour = str.substr(year_place + 1, hour_place - year_place - 1);
	int minute_place = str.find(',', hour_place + 1);
	string minute = str.substr(hour_place + 1, hour_place - minute_place - 1);
	slice_year = stoi(year);
	slice_month = stoi(month);
	slice_day = stoi(day);
	slice_hour = stoi(hour);
	slice_minute = stoi(minute);
}

int main(int argc, char **argv)
{
	int year, month, day = 0;
	if (argc != 4)
		return -1;
	else {
		year = stoi(argv[1]);
		month = stoi(argv[2]);
		day = stoi(argv[3]);
	}
	int type = -1;
	if (year == 2016) {
		switch (month) {
			case 1:
			case 2:
			case 3:
				type = 0;
				break;
			case 4:
			case 5:
			case 6:
				type = 1;
				break;				
			case 7:
			case 8:
				type = 2;
				break;
			case 9:
				type = 3;
				break;
			case 10:
			case 11:
			case 12:
				type = 4;
				break;	
		}
	}
	ifstream fin(filename[year - 2010][type]);
	ofstream sliced("slice-" + to_string(year) + "-" + to_string(month) + "-" + to_string(day) + ".csv");
	sliced<<"\'Start Hour\',\'Start Minute\',\'End Hour\',\'End Minute\',\'Start Station\',\'End Station\'"<<endl;
	int count = 0;
	string line;
	while (getline(fin, line))
	{
		if (count == 0) {
			count++;
			continue;
		}
		int t1_start = line.find(',');
		int t1_stop = line.find(',', t1_start + 1);
		string t1_time = line.substr(t1_start + 1, t1_stop - t1_start - 1);
		int t2_start = t1_stop;
		int t2_stop = line.find(',', t2_start + 1);
		string t2_time = line.substr(t2_start + 1, t2_stop - t2_start - 1);
		int t1_year, t1_month, t1_day, t1_hour, t1_minute = 0;
		int t2_year, t2_month, t2_day, t2_hour, t2_minute = 0;
		tokenize_time(t1_time, t1_year, t1_month, t1_day, t1_hour, t1_minute);
		tokenize_time(t2_time, t2_year, t2_month, t2_day, t2_hour, t2_minute);
		if ((t1_year == year) && (t1_month == month) && (t1_day == day) &&
			(t2_year == year) && (t2_month == month) && (t2_day == day)) 
		{
			int s1_start = t2_stop;
			int s1_stop = line.find(',', s1_start + 1);
			string s1 = line.substr(s1_start + 1, s1_stop - s1_start - 1);
			int s2_start = line.find(',', s1_stop + 1);
			int s2_stop = line.find(',', s2_start + 1);
			string s2 = line.substr(s2_start + 1, s2_stop - s2_start - 1);
			sliced<<t1_hour<<","<<t1_minute<<","<<t2_hour<<","<<t2_minute<<","<<s1<<","<<s2<<endl;
		}
	}	
	return 0;
}
