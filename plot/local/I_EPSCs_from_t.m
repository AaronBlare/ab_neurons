clear all;

data_path = '../../source/cpp/NS/NS';

fin = 5.0;
b = 25.0;
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

I_EPSCs = data(:, 2);

fig = figure;
hLine = plot(time, I_EPSCs);
set(gca, 'FontSize', 30);
xlabel('$t$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$I_{EPSCs}$', 'Interpreter', 'latex');
propertyeditor('on')