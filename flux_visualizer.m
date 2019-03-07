% general setting
width_interval = 100;
height_interval = 100;
clim = [50 / width_interval 1000 / height_interval ];
slicedata = importdata("./slice-2016-7-20.csv");
slice = slicedata.data;
mapdata = importdata("./map-parsed.csv");
maps = mapdata.data;
xmin = min(maps(:, 2));
xmax = max(maps(:, 2));
ymin = min(maps(:, 3));
ymax = max(maps(:, 3));
xlen = (xmax - xmin) / width_interval;
ylen = (ymax - ymin) / height_interval;

% create a mapping for geodata
mapping = containers.Map('KeyType', 'int32', 'ValueType', 'any');
for i = 1: size(maps, 1)
    mapping(maps(i, 1)) = maps(i, 2: 3);
end

start_coord = [];
end_coord = [];
% create sorted timetable for bikes
for i = 1: size(slice, 1)
    start_coord = [start_coord; mapping(slice(i, 5))];
    end_coord = [end_coord; mapping(slice(i, 6))];
end
timetable = [slice(:, 1) * 60 + slice(:, 2) slice(:, 3) * 60 + slice(:, 4) start_coord end_coord];
[~, ind] = sort(timetable(:, 1));
timetable = timetable(ind, :);

% set on-ride indices
in = [];
j = 1;
for i = 0: 1439
    while (timetable(j, 1) == i && j < 13196)
        in = [in; j]; % Update indices that are working
        j = j + 1; % update j
    end
    in(timetable(in, 2) == i) = [];  % Remove indices that are expired
    % create cell
    flux = zeros(width_interval, height_interval);
    % assign value to the cell
    if (isempty(in))
        continue; % judgment for empty matrix
    end
    for k = 1: size(in, 1)
        % calculate current coordinates
        elapsed = i - timetable(in(k), 1);
        xcoord = timetable(in(k), 3) + (timetable(in(k), 5) - timetable(in(k), 3)) / ...
                (timetable(in(k), 2) - timetable(in(k), 1)) * elapsed;
        ycoord = timetable(in(k), 4) + (timetable(in(k), 6) - timetable(in(k), 4)) / ...
                (timetable(in(k), 2) - timetable(in(k), 1)) * elapsed;
        % finding current block
        xblock = floor((xcoord - xmin) / xlen) + 1;
        yblock = floor((ycoord - ymin) / ylen) + 1;
        % saturate method
        if (xblock > width_interval)
            xblock = width_interval;
        end
        if (yblock > height_interval)
            yblock = height_interval;
        end
        flux(xblock, yblock) = flux(xblock, yblock) + 1;
    end
    imagesc([xmin xmax], [ymin ymax], flux, clim);
    colorbar;
    axis('square');
    xlabel('X Coordinates');
    ylabel('Y Coordinates');
    title("Time: " + int2str(floor(i / 60)) + ":" + int2str(mod(i, 60)));
    drawnow;
end