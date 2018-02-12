clear all;

data_path = '../../source/cpp/NS/NS';

nn = 1;
fin = 7.0;
b = 15.0;
seed = 2;

suffix = sprintf('%d_fin(%0.4f)_b(%0.4f)_seed(%d)', ...
    nn, ...
    fin, ...
    b, ...
    seed);

fn = sprintf('%s/time_%s.txt', ...
    data_path, ...
    suffix);
time = importdata(fn);

fn = sprintf('%s/data_neu_%s.txt', ...
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