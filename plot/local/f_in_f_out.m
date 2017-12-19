clear all;

data_path = '../../source/cpp/NS/NS';

f_in_start = 5.0;
f_in_shift = 1.0;
f_in_num = 1;

b = 5.0;
seed = 0;

f_out_threshold = 0.0;
f_out = zeros;
f_out_count = 1;

f_in_finish = f_in_start + (f_in_num - 1) * f_in_shift;

for f_in = f_in_start:f_in_shift:f_in_finish
    
    suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d)', ...
        f_in, ...
        b, ...
        seed);
    
    fn = sprintf('%s/time_%s.txt', ...
        data_path, ...
        suffix);
    time = importdata(fn);
    
    fn = sprintf('%s/data_%s.txt', ...
        data_path, ...
        suffix);
    data = importdata(fn);
    
    Vs = data(:, 3);
    
    threshold_crossings_count = 0;
    for i = 1:length(Vs)-1
        if (Vs(i) <= f_out_threshold) && (Vs(i+1) >= f_out_threshold)
            threshold_crossings_count = threshold_crossings_count + 1;
        end
    end
    
    num_seconds = (length(time) - 1) / 1000;
    f_out(f_out_count) = threshold_crossings_count / num_seconds;
    f_out_count = f_out_count + 1;
    
    clearvars data time Vs
end

f_in = (f_in_start:f_in_shift:f_in_finish);

f_in_kHz = (1000 ./ f_in) ./ 1000;
f_out_kHz = f_out ./ 1000;

fig = figure;
hLine = scatter(f_in_kHz, f_out_kHz);
set(gca, 'FontSize', 30);
xlabel('$f_{in}, kHz$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$f_{out}, kHz$', 'Interpreter', 'latex');
propertyeditor('on')