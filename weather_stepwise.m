clc;
clear;
for i = 2011:2016
    datedata = importdata("./datedata/datedata-" + int2str(i) + ".dat");
    weatherdata = importdata("./weatherdata/weather-data-" + int2str(i) + ".csv");
    datemat = datedata.data;
    weathermat = weatherdata.data;
    order = weathermat(:, 1) - 2010 + datemat(:, 1) / size(datemat, 1);
    [B, SE, PVAL, INMODEL, STATS] = stepwisefit([order order.^2 order.^3 sqrt(order) exp(order) log(order) order.^(-1) weathermat(:, 4:end) weathermat(:, 4:end).^2 weathermat(:, 4:end).^3 sqrt(weathermat(:, 4:end)) exp(weathermat(:, 4:end)) log(weathermat(:, 4:end)), weathermat(:, 4:end).^(-1)], datemat(:, 2), 'display', 'off', 'inmodel', [5, 7, 21, 46, 68]);
    bval(:, i - 2010) = B;
    seval(:, i - 2010) = SE;
    pval(:, i - 2010) = PVAL;
    inval(:, i - 2010) = INMODEL';
    statval(:, i - 201) = STATS;
end

invalt = sum(transpose(inval)); 
result = find(invalt >= 3) %#ok<NOPTS>