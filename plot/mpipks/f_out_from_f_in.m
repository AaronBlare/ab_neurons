clear all;

home_figures_path = '/home/yusipov/Work/ab_neurons/figures';
home_data_path = '/home/yusipov/Work/ab_neurons/data';

data_path = '/data/biophys/yusipov/ab_neurons';
data_path = sprintf('%s', data_path);

sys_id = 1;

task = 1;

ns = 90;
ns = ns * 60 * 1000;

nsps = 1000;

f_inv_start = 1.0;
f_inv_shift = 1.0;
f_inv_num = 1000;

b = 5.0;

thr_Vpost = 0.0;

seed_start = 1;
seed_num = 1;

f_in_invs = zeros(f_inv_num, 1);
f_outs = zeros(f_inv_num, 1);

for f_in_inv_id = 1:f_inv_num
    
    f_in_inv = f_inv_start + (f_in_inv_id - 1) * f_inv_shift
    f_in = 1000 / f_in_inv;
    
    f_in_invs(f_in_inv_id) = f_in_inv;
    
    f_out_avg = 0.0;
    for seed = seed_start : seed_num
    
        path_to_folder = sprintf('%s/system_%d/task_%d/ns_%d/nsps_%d/f_in_%0.4f/b_%0.4f/thr_Vpost_%0.4f/seed_%d', ...
                data_path, ...
				sys_id, ...
                task, ...
                ns, ...
                nsps, ...
                f_in, ...
                b, ...
                thr_Vpost, ...
                seed);
            
        suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d).txt', ...
                f_in, ...
                b, ...
                seed);
            
        path = sprintf('%s/f_out_%s', path_to_folder, suffix);
		data = importdata(path);
        
        f_out_avg = f_out_avg + data;
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

fn_suffix = sprintf('system(%d)_fin(%0.4f)_b(%0.4f)_seed(%d)', ...
    sys_id, ...
	f_in, ...
    b, ...
    seed);
     
savefig(sprintf('%s/f_out_from_f_in_%s.fig', home_figures_path, fn_suffix));

file_name = sprintf('%s/f_out_from_f_in_%s.txt', home_data_path, fn_suffix);
file_id = fopen(file_name, 'w');
for id = 1:size(f_outs, 1)
	fprintf(file_id, '%0.18e %0.18e\n', f_in_invs(id), f_outs(id));
end
fclose(file_id);