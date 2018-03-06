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

y1_gamma_start = -5.0;
y1_gamma_shift = 0.2;
y1_gamma_num = 26;

y2_gamma_start = 0.0;
y2_gamma_shift = 1.0;
y2_gamma_num = 1;

f_inv_start = 2.0;
f_inv_shift = 10.0;
f_inv_num = 1;

b = 2.0;

thr_Vpost = 0.0;

seed_start = 0;
seed_shift = nn;
seed_num = 20;

eta_window = 8.0;

y1_gammas = zeros(y1_gamma_num, 1);
etas = zeros(y1_gamma_num, 1);

for y1_gamma_id = 1:y1_gamma_num
    
    y1_gamma = y1_gamma_start + (y1_gamma_id - 1) * y1_gamma_shift
    y1_gammas(y1_gamma_id) = y1_gamma;
    
    for y2_gamma_id = 1:y2_gamma_num
        
        y2_gamma = y2_gamma_start + (y2_gamma_id - 1) * y2_gamma_shift;
        
        f_in = f_inv_start;
		
        eta_curr = 0.0;
        
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
            
            path = sprintf('%s/eta_%s', path_to_folder, suffix);
            data = importdata(path);
            
            eta_curr = eta_curr + data;
            
        end
        
        etas(y1_gamma_id) = eta_curr / seed_num;
    end
end

fig = figure;
hLine = plot(y1_gammas, etas);
set(gca, 'FontSize', 30);
xlabel('$\gamma_1$', 'Interpreter', 'latex');
set(gca, 'FontSize', 30);
ylabel('$\eta$', 'Interpreter', 'latex');

fn_suffix = sprintf('system(%d)_gamma1(%0.4f)_gamma2(%0.4f)_fin(%0.4f)_b(%0.4f)_seed(%d)', ...
    sys_id, ...
    y1_gamma, ...
    y2_gamma, ...
    f_in, ...
    b, ...
    seed);

savefig(sprintf('%s/eta_from_gamma_1_%s.fig', home_figures_path, fn_suffix));

file_name = sprintf('%s/eta_from_gamma_1_%s.txt', home_data_path, fn_suffix);
file_id = fopen(file_name, 'w');
for y1_id = 1:size(y1_gammas, 1)
    fprintf(file_id, '%0.18e %0.18e\n', y1_gammas(y1_id), etas(y1_id));
end
fclose(file_id);