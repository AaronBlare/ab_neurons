clear all;

data_path = '../../source/cpp/NS/NS';

fin = 5.0;
b = 5.0;
seed = 0;

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

x = data(:, 1);

fig = figure;
hLine = plot(time, x);
set(gca, 'FontSize', 30);
xlabel('$t$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$x$', 'Interpreter', 'latex');
propertyeditor('on')

