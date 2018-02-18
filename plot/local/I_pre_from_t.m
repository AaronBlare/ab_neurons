clear all;

data_path = '../../source/cpp/NS/NS';

nn = 2;
fin = 1;
b = 15.0;
seed = 8;

suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d)', ...
        fin, ...
        b, ...
        seed);

fn = sprintf('%s/time_%s.txt', ...
        data_path, ...
        suffix);
time = importdata(fn);

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
    
    Is = data(:, 7);
    
    subplot(nn, 1, n_id);
    hLine = bar(time - 0.5, Is);
    set(gca, 'FontSize', 15);
    xlabel('$t, ms$', 'Interpreter', 'latex');
    xlim([0 100])
    set(gca, 'FontSize', 15);
    ylabel('$I$', 'Interpreter', 'latex');
    ylim([0 2])
    set(gca, 'FontSize', 15);
    title(sprintf('$neuron %d$', n_id), 'Interpreter', 'latex');
    
    clearvars data Vs
    
end