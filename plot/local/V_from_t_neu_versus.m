clear all;

data_path = '../../source/cpp/NS/NS';

nn = 2;
fin = 5;
b = 4.0;
seed = 8;

suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d)', ...
        fin, ...
        b, ...
        seed);

fn = sprintf('%s/time_%s.txt', ...
        data_path, ...
        suffix);
time = importdata(fn);


data_path_pev = '../../source/cpp/pev/pev';

figure

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
    
    fn = sprintf('%s/V.txt', ...
        data_path_pev);
    data = importdata(fn);
    
    Vs_pev = data(:, n_id);
    
    subplot(nn, 1, n_id);
    hLine = plot(time, log10(abs(Vs - Vs_pev) + 1.0e-16));
    set(gca, 'FontSize', 15);
    xlabel('$t, ms$', 'Interpreter', 'latex');
    set(gca, 'FontSize', 15);
    ylabel('$\log_{10}diff(V)$', 'Interpreter', 'latex');
    set(gca, 'FontSize', 15);
    title(sprintf('$neuron %d$', n_id), 'Interpreter', 'latex');
    
    clearvars data Vs Vs_pev
    
end