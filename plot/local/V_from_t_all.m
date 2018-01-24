clear all;

data_path = '../../source/cpp/NS/NS';

fins = [10.0 3.3 2.0 1.43 1.11];
fins_real = round(1000./fins, -2);
b = 5.0;
seed = 0;

for fin_id = 1:length(fins)
    
    fin = fins(fin_id);
    
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
    
    subplot(length(fins), 1, fin_id);
    hLine = plot(time./60000, Vs);
    set(gca, 'FontSize', 15);
    xlabel('$t, min$', 'Interpreter', 'latex');
    set(gca, 'FontSize', 15);
    ylabel('$V$', 'Interpreter', 'latex');
    set(gca, 'FontSize', 15);
    title(sprintf('$f_{in} = %0.1f$ kHz', fins_real(fin_id) / 1000), 'Interpreter', 'latex');
    
    clearvars data time Vs
    
end