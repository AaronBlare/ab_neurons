clear all;

data_path = '../../source/cpp/NS/NS';

nn = 4;
fin = 4;
b = 5.0;
seed = 8;

suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d)', ...
        fin, ...
        b, ...
        seed);

fn = sprintf('%s/time_%s.txt', ...
        data_path, ...
        suffix);
time = importdata(fn);

for n_id = 1:nn
    
    suffix = sprintf('%d_fin(%0.4f)_b(%0.4f)_seed(%d)', ...
        n_id - 1, ...
        fin, ...
        b, ...
        seed);
    
    fn = sprintf('%s/data_neu_%s.txt', ...
        data_path, ...
        suffix);
    data = importdata(fn);
    
    Vs = data(:, 3);
    
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