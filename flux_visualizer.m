function overflux = flux_visualizer(year, month, day, compiling, plotting)
    if (nargin == 3)
        compiling = true;
        plotting = true;
    end
    
    % csv generation setting
    if (compiling)
        compile = system("g++ ./data_slicer.cpp -o ./data_slicer");
        if (compile ~= 0)
            error("C++ compilation failed.");
        else
            run = system("./data_slicer " + int2str(year) + " " + int2str(month) + " " + int2str(day));
            if (run ~= 0)
                error("CSV data generation failed.");
            end
        end
    end
    
    % general setting
    overflux = [];
    width_interval = 100;
    height_interval = 100;
    clim = [50 / width_interval 1000 / height_interval ];
    slicedata = importdata("./slice-" + int2str(year) + "-" + int2str(month) + "-" + int2str(day) + ".csv");
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
        if (mapping.isKey(slice(i, 5)) && mapping.isKey(slice(i, 6)))
            start_coord = [start_coord; mapping(slice(i, 5))];
            end_coord = [end_coord; mapping(slice(i, 6))];
        else
            start_coord = [start_coord; [nan, nan]];
            end_coord = [end_coord; [nan, nan]];
        end
    end
    timetable = [slice(:, 1) * 60 + slice(:, 2) slice(:, 3) * 60 + slice(:, 4) start_coord end_coord];
    [~, ind] = sort(timetable(:, 1));
    timetable = timetable(ind, :);

    % set on-ride indices
    in = [];
    j = 1;
    for i = 0: 1439
        while (timetable(j, 1) == i && j < size(timetable, 1))
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
            if (isfinite(xblock) && isfinite(yblock))
                flux(xblock, yblock) = flux(xblock, yblock) + 1;
                if (flux(xblock, yblock) > clim(2))
                    overflux = [overflux; [floor(i / 60), mod(i, 60), xblock, yblock]];
                end
            end
        end
        if (plotting)
            imagesc([xmin xmax], [ymin ymax], flux, clim);
            colorbar;
            colormap([1: -0.01: 0; 1: -0.01: 0; 1: -0.01: 0]');
            axis('square');
            xlabel('X Coordinates');
            ylabel('Y Coordinates');
            title("Time: " + int2str(floor(i / 60)) + ":" + int2str(mod(i, 60)));
            drawnow;
        end
    end
end