cd timedata;
for val in `ls -1 | grep .plt$ `; do
	gnuplot --persist $val;
done
cd ..;

cd datedata;
for val in `ls -1 | grep .plt$`; do
	gnuplot --persist $val;
done
cd ..;