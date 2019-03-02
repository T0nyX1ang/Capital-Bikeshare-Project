data0 = importdata("./yeardata.dat"); 
year = data0.data(:, 1);
count = data0.data(:, 2);
figure(1);
plot(year, count)
for i = 0: 6
    spring(i + 1) = count(i * 4 + 2);
    summer(i + 1) = count(i * 4 + 3);
    autumn(i + 1) = count(i * 4 + 4);
    winter(i + 1) = count(i * 4 + 1);
end

figure(2);
plot(1: 7, spring);
hold on;
plot(1: 7, summer);
hold on;
plot(1: 7, autumn);
hold on;
plot(1: 7, winter);
hold on;