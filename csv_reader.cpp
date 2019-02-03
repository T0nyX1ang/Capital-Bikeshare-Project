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
	int countable_date[12 * 31];
	int hour[24];
	int minute[60];
	int countable_time[1440];
} time_data;

void tokenize_time(string str) 
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
	time_data.month[stoi(month) - 1]++;
	time_data.date[stoi(date) - 1]++;
	time_data.year[stoi(year) - 2010]++;
	time_data.hour[stoi(hour)]++;
	time_data.minute[stoi(minute)]++;
	time_data.countable_date[(stoi(month) - 1) * 31 + stoi(date) - 1]++;
	time_data.countable_time[stoi(hour) * 60 + stoi(minute)]++;
}

void print() 
{
	for (int i = 0; i < 8; i++)
		cout<<"Year "<<(i + 2010)<<": "<<time_data.year[i]<<endl;
	cout<<endl;
	for (int i = 0; i < 12; i++)
		cout<<"Month "<<(i + 1)<<": "<<time_data.month[i]<<endl;
	cout<<endl;
	for (int i = 0; i < 31; i++)
		cout<<"Date "<<(i + 1)<<": "<<time_data.date[i]<<endl;
	cout<<endl;
	for (int i = 0; i < 24; i++)
		cout<<"Hour "<<i<<": "<<time_data.hour[i]<<endl;
	cout<<endl;
	for (int i = 0; i < 60; i++)
		cout<<"Minute "<<i<<": "<<time_data.minute[i]<<endl;
	cout<<endl;
	for (int i = 0; i < 1440; i++)
		cout<<"Time "<<i<<": "<<time_data.countable_time[i]<<endl;
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 31; j++)
			cout<<"Month: "<<(i + 1)<<", Date: "<<(j + 1)<<": "<<time_data.countable_date[i * 31 + j]<<endl;
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

void data() 
{
	ofstream time_file("timedata.dat");
	time_file<<"time count"<<endl;
	for (int i = 0; i < 1440; i++)
		time_file<<i<<" "<<time_data.countable_time[i]<<endl;
	time_file.close();

	ofstream date_file("datedata.dat");
	int datecount = 1;
	date_file<<"date count"<<endl;
	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 31; j++)
			if (time_data.countable_date[i * 31 + j] != 0 || validate_date(i + 1, j + 1)) 
			{
				date_file<<datecount<<" "<<time_data.countable_date[i * 31 + j]<<endl;
				datecount++;
			}
}

int main()
{
	string filename[5] = {"2016-Q1-Trips-History-Data.csv","2016-Q2-Trips-History-Data.csv","2016-Q3-Trips-History-Data-1.csv","2016-Q3-Trips-History-Data-2.csv","2016-Q4-Trips-History-Data.csv"};
	for (int i = 0; i < 5; ++i)
	{
		ifstream fin(filename[i]);
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
			tokenize_time(split);
			count++;
		}
	}
	print();
	data();
	return 0;
}