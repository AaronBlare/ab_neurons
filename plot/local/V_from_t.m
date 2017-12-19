clear all;

data_path = '../../source/cpp/NS/NS';

fin = 10.0;
b = 5.0;
seed = 111;

suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d)', ...
    fin, ...
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

fig = figure;
hLine = plot(time, Vs);
set(gca, 'FontSize', 30);
xlabel('$t, ms$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$V$', 'Interpreter', 'latex');
propertyeditor('on')