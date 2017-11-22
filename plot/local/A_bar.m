clear all;

data_path = '../../source/cpp/NS/NS';

fin = 200.0;
b = 5.0;
seed = 1337;

num_bins = 30;

suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d)', ...
    fin, ...
    b, ...
    seed);

fn = sprintf('%s/A_%s.txt', ...
    data_path, ...
    suffix);
A = importdata(fn);

fig = figure;
h = hist(A, num_bins);
h = h/sum(h);
hLine = bar(h);
set(gca, 'FontSize', 30);
xlabel('$A$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$PDF$', 'Interpreter', 'latex');
propertyeditor('on')