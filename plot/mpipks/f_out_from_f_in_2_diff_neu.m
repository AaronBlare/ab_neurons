clear all;

home_figures_path = '/home/yusipov/Work/ab_neurons/figures';
home_data_path = '/home/yusipov/Work/ab_neurons/data';

data_path = '/data/biophys/yusipov/ab_neurons/1_const_fin_1_changing_fin';
data_path = sprintf('%s', data_path);

sys_id = 1;

task = 1;

nn = 2;

ns = 10;
ns = ns * 60 * 1000;

nsps = 1000;

y1_gamma = -5.0;
y2_gamma = 0.0;

f_inv_start = 1.0;
f_inv_shift = 50.0;
f_inv_num = 21;

b = 10.0;

thr_Vpost = 0.0;

seed_start = 0;
seed_shift = nn;
seed_num = 20;

eta_window = 8.0;

f_in_invs = zeros(f_inv_num, 1);
f_outs = zeros(f_inv_num, 1);

for f_in_inv_id = 1:f_inv_num
    
    f_in_inv = f_inv_start + (f_in_inv_id - 1) * f_inv_shift
    f_in = 1000 / f_in_inv;
    
    f_in_invs(f_in_inv_id) = f_in_inv;
    
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
        
        f_out_avg = f_out_curr / nn;
    end
    f_out_avg = f_out_avg / seed_num;
    
    f_outs(f_in_inv_id) = f_out_avg;
    
end

fig = figure;
hLine = plot(f_in_invs, f_outs);
set(gca, 'FontSize', 30);
xlabel('$f_{in}$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$f_{out}$', 'Interpreter', 'latex');

fn_suffix = sprintf('system(%d)_gamma1(%0.4f)_gamma2(%0.4f)_fin(%0.4f)_b(%0.4f)_seed(%d)', ...
    sys_id, ...
    y1_gamma, ...
    y2_gamma, ...
    f_in, ...
    b, ...
    seed);

savefig(sprintf('%s/f_out_from_f_in_2_diff_neu_%s.fig', home_figures_path, fn_suffix));

file_name = sprintf('%s/f_out_from_f_in_2_diff_neu_%s.txt', home_data_path, fn_suffix);
file_id = fopen(file_name, 'w');
for id = 1:size(f_outs, 1)
    fprintf(file_id, '%0.18e %0.18e\n', f_in_invs(id), f_outs(id));
end
fclose(file_id);