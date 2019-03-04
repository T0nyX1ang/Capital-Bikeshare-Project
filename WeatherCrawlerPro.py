import csv
import json
import requests
import bs4
import time

def get_range(year, month):
	days = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
	if (year % 4 != 0 or (year % 100 == 0 and year % 400 != 0)):
		days[1] = 28
	months = ['01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12']
	return str(year) + months[month - 1] + '01' + str(year) + months[month - 1] + str(days[month - 1])

def crawler(year, month):
	print("Current range token:", get_range(year, month))
	url = "https://api-ak.wunderground.com/api/d8585d80376a429e/history_" + get_range(year, month) + "/lang:EN/units:english/bestfct:1/v:2.0/q/KDCA.json?showObs=0&ttl=120"
	headers = {
		'Host': 'api-ak.wunderground.com',
		'Connection': 'keep-alive',
		'Origin': 'https://www.wunderground/com',
		'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36',
		'Referer': 'httsp://www.wunderground.com/history/month/us/dc/washington/KDCA/date/' + str(year) + '-' + str(month),
		'Accept': 'application/json, text/plain, */*',
		'Accept-Encoding': 'gzip, deflate, br',
	}
	cookies = {
		'DHT': '1',
	}
	r = requests.get(url, headers=headers, cookies=cookies)
	jsdata = r.json()
	history = jsdata['history']
	days = history['days']
	for val in days:
		summary = val['summary']
		date = summary['date']
		year = date['year']
		month = date['month']
		day = date['day']
		min_temp = summary['min_temperature']
		max_temp = summary['max_temperature']
		precipitation = summary['precip']
		visibility = summary['visibility']
		wind_speed = summary['wind_speed']
		has_fog = summary['fog']
		has_hail = summary['hail']
		has_rain = summary['rain']
		has_snow = summary['snow']
		has_snowfall = summary['snowfall']
		has_thunder = summary['thunder']
		has_tornado = summary['tornado']
		csv_write.writerow([int(year), int(month), int(day), float(max_temp), float(min_temp), float(precipitation),
							float(visibility), float(wind_speed), int(has_fog), int(has_hail), int(has_rain), int(has_snow),
							int(has_snowfall), int(has_thunder), int(has_tornado)])

for year in range(2010, 2018):
	w = open('./weatherdata/weather-data-' + str(year) + '.csv', 'w', newline='') # open writable file
	csv_write = csv.writer(w, dialect='excel') # csv mode
	csv_write.writerow(['\"Year\"', 
						'\"Month\"', 
						'\"Day\"', 
						'\"Highest Temperature\"', 
						'\"Lowest Temperature\"', 
						'\"Precipitation\"',
						'\"Visibility\"',
						'\"Wind Speed\"',
						'\"Has_fog\"',
						'\"Has_hail\"',
						'\"Has_rain\"',
						'\"Has_snow\"',
						'\"Has_snowfall\"',
						'\"Has_thunder\"',
						'\"Has_tornado\"',])
	for month in range(1, 13):
		crawler(year, month)
		print("Year:", year, "Month:", month, "crawled.", "Sleeping for 3 seconds.")
		time.sleep(3) # web-spider friendly
	w.close()