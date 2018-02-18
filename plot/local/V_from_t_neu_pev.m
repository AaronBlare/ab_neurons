clear all;

data_path = '../../source/cpp/NS/NS';

nn = 2;
fin = 1;
b = 25.0;
seed = 8;

suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d)', ...
        fin, ...
        b, ...
        seed);

fn = sprintf('%s/time_%s.txt', ...
        data_path, ...
        suffix);
time = importdata(fn);

data_path = '../../source/cpp/pev/pev';

figure

for n_id = 1:nn
    
    fn = sprintf('%s/V.txt', ...
        data_path);
    data = importdata(fn);
    
    Vs = data(:, n_id);
    
    subplot(nn, 1, n_id);
    hLine = plot(time, Vs);
    set(gca, 'FontSize', 15);
    xlabel('$t, ms$', 'Interpreter', 'latex');
    set(gca, 'FontSize', 15);
    ylabel('$V$', 'Interpreter', 'latex');
    set(gca, 'FontSize', 15);
    title(sprintf('$neuron %d$', n_id), 'Interpreter', 'latex');
    
    clearvars data Vs
    
end