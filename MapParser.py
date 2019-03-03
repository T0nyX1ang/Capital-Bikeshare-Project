import json
import csv

r = open('./map-inventory.json', 'U') # open file
w = open('./map-parsed.csv', 'w', newline='') # open writable file
csv_write = csv.writer(w, dialect='excel') # csv mode
jsdata = r.read() # read file
dicdata = json.loads(jsdata) # convert json to dict
csv_write.writerow(['Station Number', 'X Coordinate', 'Y Coordinate'])

for val in dicdata['features']:
	geodata = val['geometry'];
	(coord_x, coord_y) = geodata['coordinates']
	propdata = val['properties']
	stationdata = propdata['station']
	station_no = stationdata['terminal']
	csv_write.writerow([station_no, coord_x, coord_y])
	print(val)

w.close()
r.close()