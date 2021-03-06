clear all;

home_figures_path = '/home/yusipov/Work/ab_neurons/figures';
home_data_path = '/home/yusipov/Work/ab_neurons/data';

data_path = '/data/biophys/yusipov/ab_neurons/gamma_1_from_gamma_2';
data_path = sprintf('%s', data_path);

sys_id = 1;

task = 1;

nn = 2;

ns = 10;
ns = ns * 60 * 1000;

nsps = 1000;

y1_gamma_start = 0.0;
y1_gamma_shift = 0.2;
y1_gamma_num = 1;

y2_gamma_start = 0.0;
y2_gamma_shift = 0.2;
y2_gamma_num = 26;

f_inv_start = 2.0;
f_inv_shift = 10.0;
f_inv_num = 1;

b = 2.0;

thr_Vpost = 0.0;

seed_start = 0;
seed_shift = nn;
seed_num = 20;

eta_window = 8.0;

y2_gammas = zeros(y1_gamma_num, 1);
f_outs = zeros(f_inv_num, 1);

for y1_gamma_id = 1:y1_gamma_num
    
    y1_gamma = y1_gamma_start + (y1_gamma_id - 1) * y1_gamma_shift;
    
    for y2_gamma_id = 1:y2_gamma_num
        
        y2_gamma = y2_gamma_start + (y2_gamma_id - 1) * y2_gamma_shift
        y2_gammas(y2_gamma_id) = y2_gamma;
        
        for f_inv_id = 1:f_inv_num
            
            f_in = f_inv_start + (f_inv_id - 1) * f_inv_shift;
            f_ins(f_inv_id) = f_in;
            
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
                    f_in, ...
                    b, ...
                    thr_Vpost, ...
                    eta_window , ...
                    seed);
                
                suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d).txt', ...
                    f_in, ...
                    b, ...
                    seed);
                
                f_out_curr = 0.0;
                
                for n_id = 1: nn
                    
                    path = sprintf('%s/f_out_%d_%s', path_to_folder, (n_id - 1), suffix);
                    data = importdata(path);
                    
                    f_out_curr = f_out_curr + data;
                    
                end
                
                f_out_curr = f_out_curr / nn;
            end
            
            f_outs(y2_gamma_id) = f_out_curr / seed_num;
        end
    end
end

for y2_id = 1:length(f_outs)
    f_outs(y2_id) = f_outs(y2_id) * 1000;
end

fig = figure;
hLine = plot(y2_gammas, f_outs);
set(gca, 'FontSize', 30);
xlabel('$\gamma_2$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$f_{out}$', 'Interpreter', 'latex');

fn_suffix = sprintf('system(%d)_gamma1(%0.4f)_gamma2(%0.4f)_fin(%0.4f)_b(%0.4f)_seed(%d)', ...
    sys_id, ...
    y1_gamma, ...
    y2_gamma, ...
    f_in, ...
    b, ...
    seed);

savefig(sprintf('%s/f_out_from_gamma_2_%s.fig', home_figures_path, fn_suffix));

file_name = sprintf('%s/f_out_from_gamma_2_%s.txt', home_data_path, fn_suffix);
file_id = fopen(file_name, 'w');
for y2_id = 1:length(y2_gammas)
    fprintf(file_id, '%0.18e %0.18e\n', y2_gammas(y2_id), f_outs(y2_id));
end
fclose(file_id);