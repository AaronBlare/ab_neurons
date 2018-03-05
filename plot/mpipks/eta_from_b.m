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

y1_gamma = -3.0;
y2_gamma = 0.0;

f_inv_start = 5.0;
f_inv_shift = 1.0;
f_inv_num = 1;

b_start = 1.0;
b_shift = 1.0;
b_num = 50;

thr_Vpost = 0.0;

eta_window = 8.0;

seed_start = 0;
seed_shift = nn;
seed_num = int32(20 / nn);

bs = zeros(b_num, 1);
etas = zeros(b_num, 1);

for b_id = 1:b_num
    
    b = b_start + (b_id - 1) * b_shift
    
    bs(b_id) = b;
    
    eta_avg = 0.0;
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
            
        path = sprintf('%s/eta_%s', path_to_folder, suffix);
		data = importdata(path);
        
        eta_avg = eta_avg + data;
    end 
    eta_avg = eta_avg / seed_num;
    
    etas(b_id) = eta_avg;
    
end

fig = figure;
hLine = plot(bs, etas);
set(gca, 'FontSize', 30);
xlabel('$b$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$\eta$', 'Interpreter', 'latex');

fn_suffix = sprintf('system(%d)_gamma1(%0.4f)_gamma2(%0.4f)_fin(%0.4f)_b(%0.4f)_etaw(%0.4f)', ...
    sys_id, ...
	y1_gamma, ...
	y2_gamma, ...
	f_inv_start, ...
    b, ...
	eta_window);
     
savefig(sprintf('%s/eta_from_b_%s.fig', home_figures_path, fn_suffix));

file_name = sprintf('%s/eta_from_b_%s.txt', home_data_path, fn_suffix);
file_id = fopen(file_name, 'w');
for id = 1:size(bs, 1)
	fprintf(file_id, '%0.18e %0.18e\n', bs(id), etas(id));
end
fclose(file_id);