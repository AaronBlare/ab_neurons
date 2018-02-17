clear all;

home_figures_path = '/home/yusipov/Work/ab_neurons/figures';
home_data_path = '/home/yusipov/Work/ab_neurons/data';

data_path = '/data/biophys/yusipov/ab_neurons/eta_from_b_without_g';
data_path = sprintf('%s', data_path);

sys_id = 1;

task = 1;

nn = 2;

ns = 90;
ns = ns * 60 * 1000;

nsps = 1000;

y1_gamma = 0.0;
y2_gamma = 0.0;

f_inv_start = 7.0;
f_inv_shift = 1.0;
f_inv_num = 1;

b_start = 1.0;
b_shift = 1.0;
b_num = 50;

thr_Vpost = 0.0;

eta_window = 8.0;

seed_start = 0;
seed_shift = nn;
seed_num = 20;

bs = zeros(b_num, 1);
fouts = zeros(b_num, 1);

for b_id = 1:b_num
    
    b = b_start + (b_id - 1) * b_shift
    
    bs(b_id) = b;
    
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
                b, ...
				thr_Vpost, ...
                eta_window , ...
                seed);
            
        suffix = sprintf('fin(%0.4f)_b(%0.4f)_seed(%d).txt', ...
                f_inv_start, ...
                b, ...
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
    
    fouts(b_id) = f_out_avg;
    
end

fig = figure;
hLine = plot(bs, fouts);
set(gca, 'FontSize', 30);
xlabel('$b_{0}$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$f_{out}$', 'Interpreter', 'latex');

fn_suffix = sprintf('system(%d)_gamma1(%0.4f)_gamma2(%0.4f)_fin(%0.4f)_b(%0.4f)_etaw(%0.4f)', ...
    sys_id, ...
	y1_gamma, ...
	y2_gamma, ...
	f_inv_start, ...
    b, ...
	eta_window);
     
savefig(sprintf('%s/f_out_from_b_%s.fig', home_figures_path, fn_suffix));

file_name = sprintf('%s/f_out_from_b_%s.txt', home_data_path, fn_suffix);
file_id = fopen(file_name, 'w');
for id = 1:size(bs, 1)
	fprintf(file_id, '%0.18e %0.18e\n', bs(id), fouts(id));
end
fclose(file_id);