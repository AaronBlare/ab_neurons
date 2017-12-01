clear all;

data_path = '../../source/cpp/NS/NS';

fin = 5.0;
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

fn = sprintf('%s/I_pre_%s.txt', ...
    data_path, ...
    suffix);
I_pre = importdata(fn);

fig = figure;
hLine = plot(time, I_pre);
set(gca, 'FontSize', 30);
xlabel('$t$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$I_{pre}$', 'Interpreter', 'latex');
ylim([-0.25 1.25])
propertyeditor('on')

