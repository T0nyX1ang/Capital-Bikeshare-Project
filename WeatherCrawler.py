import requests
import bs4
import csv
import time

def crawler(year, month):
	url = "http://www.tianqihoubao.com/guoji/3195/" + str(year) + "-" + str(month) + ".html"
	headers = {
		'Host': 'www.tianqihoubao.com',
		'Connection': 'keep-alive',
		'User-Agent': 'Chrome/72.0.3626.119',
		'Referer': 'http://www.tianqihoubao.com/guoji/3195/',
	}
	cookies = {
		'DHT': '1',
	}
	r = requests.get(url, headers=headers, cookies=cookies)
	bs_r = bs4.BeautifulSoup(r.text, features='lxml')
	bs_table = bs_r.find('table')
	tr_count = 0
	for tr in bs_table.find_all('tr'):
		if (tr_count == 0):
			tr_count += 1
			continue
		td_count = 0
		# Re-generate data
		year = 0
		month = 0
		date = 0
		h_temp = 0;
		l_temp = 0;
		weather_type = 0;
		for td in tr.find_all('td'):
			if td_count == 0:
				orig_date = td.get_text().replace('\n', '').replace('\r', '').replace(' ', '')
				(yearstr, monthdate) = orig_date.split("年")
				(monthstr, datedate) = monthdate.split("月")
				(datestr, nulldate) = datedate.split("日")
				year = int(yearstr)
				month = int(monthstr)
				date = int(datestr)

			elif td_count == 1:
				orig_weather = td.get_text().replace('\n', '').replace('\r', '').replace(' ', '')
				(first_weather, last_weather) = orig_weather.split('/')
				if '雪' in first_weather:
					weather_type += -2
				elif '雨' in first_weather:
					weather_type += -1
				elif '阴' in first_weather:
					weather_type += 0
				elif '多云' in first_weather:
					weather_type += 1
				elif '晴' in first_weather:
					weather_type += 2

				if '雪' in last_weather:
					weather_type += -2
				elif '雨' in last_weather:
					weather_type += -1
				elif '阴' in last_weather:
					weather_type += 0
				elif '多云' in last_weather:
					weather_type += 1
				elif '晴' in last_weather:
					weather_type += 2

			elif td_count == 2:
				orig_temperate = td.get_text().replace('\n', '').replace('\r', '').replace(' ', '').replace('℃', '')
				(highstr, lowstr) = orig_temperate.split("/")
				h_temp = int(highstr.replace("°C", ""))
				l_temp = h_temp if lowstr is '' else int(lowstr.replace("°C", ""))


			elif td_count == 3:
				pass

			else:
				raise IndexError("Index out of range.")

			td_count += 1
		# generate row into csv
		csv_write.writerow([year, month, date, weather_type, h_temp, l_temp])

for year in range(2014, 2018):
	w = open('./weather-data-' + str(year) + '.csv', 'w', newline='') # open writable file
	csv_write = csv.writer(w, dialect='excel') # csv mode
	csv_write.writerow(['Year', 'Month', 'Date', 'Weather Type', 'Highest Temperature', 'Lowest Temperature'])
	for month in range(1, 13):
		crawler(year, month)
		print("Year:", year, "Month:", month, "crawled.")
		time.sleep(3) # web-spider friendly
	w.close()