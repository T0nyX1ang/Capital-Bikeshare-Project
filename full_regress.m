clc;
clear;
%#ok<*AGROW>
datemat = [];
weathermat = [];
order = [];
for i = 2011:2016
    datedata = importdata("./datedata/datedata-" + int2str(i) + ".dat");
    weatherdata = importdata("./weatherdata/weather-data-" + int2str(i) + ".csv");
    tempdate = datedata.data;
    datemat = [datemat; datedata.data];
    weathermat = [weathermat; weatherdata.data];
    order = [order; i - 2010 + (tempdate(:, 1) - 1) / size(tempdate, 1)];
end

[b, bint, r, rint, stats] = regress(datemat(:, 2), [ones(size(datemat, 1), 1) exp(order) log(order) order.^(-1) weathermat(:, [5, 7, 11]) weathermat(:, [5]).^2 weathermat(:, [5, 8]).^3 sqrt(weathermat(:, [4, 6])), exp(weathermat(:, [])), log(weathermat(:, [4])) weathermat(:, []).^(-1)]);  %#ok<NBRAK>
%figure(1);
%rcoplot(r, rint);
datedata = importdata("./datedata/datedata-2017.dat");
weatherdata = importdata("./weatherdata/weather-data-2017.csv");
tempdate = datedata.data;
datemat = datedata.data;
weathermat = weatherdata.data;
order = i - 2010 + (tempdate(:, 1) - 1) / size(tempdate, 1);
figure(2);
range = 1: 90;
plot(range, [ones(size(range, 2), 1) exp(order(range)) log(order(range)) order(range).^(-1) weathermat(range, [5, 7, 11]) weathermat(range, [5]).^2 weathermat(range, [5, 8]).^3 sqrt(weathermat(range, [4, 6])), exp(weathermat(range, [])), log(weathermat(range, [4])) weathermat(range, []).^(-1)] * b);  %#ok<NBRAK>
hold on;
plot(range, datemat(range, 2))