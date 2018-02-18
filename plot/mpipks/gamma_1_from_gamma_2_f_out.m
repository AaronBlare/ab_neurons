clear all;

home_figures_path = '/home/yusipov/Work/ab_neurons/figures';
home_data_path = '/home/yusipov/Work/ab_neurons/data';

data_path = '/data/biophys/yusipov/ab_neurons/gamma_1_from_gamma_2';
data_path = sprintf('%s', data_path);

sys_id = 1;

task = 1;

nn = 2;

ns = 90;
ns = ns * 60 * 1000;

nsps = 1000;

y1_gamma_start = -3.0;
y1_gamma_shift = 0.1;
y1_gamma_num = 31;

y2_gamma_start = 0.0;
y2_gamma_shift = 0.1;
y2_gamma_num = 51;

f_inv_start = 5.0;
f_inv_shift = 1.0;
f_inv_num = 1;

b_start = 4.0;
b_shift = 1.0;
b_num = 1;

thr_Vpost = 0.0;

eta_window = 8.0;

seed_start = 0;
seed_shift = nn;
seed_num = 1;

y1_gammas = zeros(y1_gamma_num, 1);
y2_gammas = zeros(y2_gamma_num, 1);
f_outs = zeros(y1_gamma_num, y2_gamma_num);

for y1_gamma_id = 1:y1_gamma_num
    
    y1_gamma = y1_gamma_start + (y1_gamma_id - 1) * y1_gamma_shift
    y1_gammas(y1_gamma_id) = y1_gamma;
    
    for y2_gamma_id = 1:y2_gamma_num
        
        y2_gamma = y2_gamma_start + (y2_gamma_id - 1) * y2_gamma_shift;
        y2_gammas(y2_gamma_id) = y2_gamma;
        
        f_out_avg = 0.0;
        for seed_id = 1 : seed_num
            
            seed = seed_start + (seed_id - 1) * seed_shift;
            
            path_to_folder = sprintf('%s/system_%d/task_%d/nn_%d/ns_%d/nsps_%d/y1_gamma_%0.4f/y2_gamma_%0.4f/f_in_%0.4f/b_%0.4f/thr_Vpost_%0.4f/eta_%0.4f/seed_%d', ...
                data_path, ...
                sys_id, ...
                task, ...
                nn, ...
                ns, ...
                nsps, ...
                y1_gamma, ...
                y2_gamma, ...
                f_inv_start, ...
                b_start, ...
                thr_Vpost, ...
                eta_window , ...
                seed);
            
            suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d).txt', ...
                f_inv_start, ...
                b_start, ...
                seed);
            
            f_out_curr = 0.0;
            
            for n_id = 1: nn
                
                path = sprintf('%s/f_out_%d_%s', path_to_folder, (n_id - 1), suffix);
                data = importdata(path);
                
                f_out_curr = f_out_curr + data;
                
            end
            
            f_out_avg = f_out_avg + f_out_curr / nn;
			
        end
        f_out_avg = f_out_avg / seed_num;
        
        f_outs(y1_gamma_id, y2_gamma_id) = f_out_avg;
    end
end

fig = figure;

hLine = imagesc(y1_gammas, y2_gammas, f_outs);
set(gca, 'FontSize', 30);
xlabel('$\gamma_1$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$\gamma_2$', 'Interpreter', 'latex');
colormap hot;
h = colorbar;
set(gca, 'FontSize', 30);
title(h, 'f_{out}', 'FontSize', 33);
set(gca,'YDir','normal');
hold all;

fn_suffix = sprintf('system(%d)_gamma1(%0.4f)_gamma2(%0.4f)_fin(%0.4f)_b(%0.4f)_etaw(%0.4f)', ...
    sys_id, ...
    y1_gamma, ...
    y2_gamma, ...
    f_inv_start, ...
    b_start, ...
    eta_window);

savefig(sprintf('%s/gamma_1_from_gamma_2_f_out_%s.fig', home_figures_path, fn_suffix));

file_name = sprintf('%s/gamma_1_from_gamma_2_f_out_%s.txt', home_data_path, fn_suffix);
file_id = fopen(file_name, 'w');
for y1_id = 1:size(y1_gammas, 1)
    for y2_id = 1:size(y2_gammas, 1)
        fprintf(file_id, '%0.18e %0.18e %0.18e\n', y1_gammas(y1_id), y2_gammas(y2_id), f_outs(y1_id, y2_id));
    end
end
fclose(file_id);