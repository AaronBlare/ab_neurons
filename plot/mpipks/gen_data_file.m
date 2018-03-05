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

y1_gamma_start = -5.0;
y1_gamma_shift = 0.1;
y1_gamma_num = 51;

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

result_data = zeros(y1_gamma_num * y2_gamma_num, (5 + 2*nn));
str_num = 1;

for y1_gamma_id = 1:y1_gamma_num
    
    y1_gamma = y1_gamma_start + (y1_gamma_id - 1) * y1_gamma_shift
    
    for y2_gamma_id = 1:y2_gamma_num
        
        y2_gamma = y2_gamma_start + (y2_gamma_id - 1) * y2_gamma_shift;
        
        num_spikes_avg = zeros(nn, 1);
		nss_avg = 0.0; 
		eta_avg = 0.0;
		f_out_avg = zeros(nn, 1);
		mean_f_out = 0.0;
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
				
			path_nss = sprintf('%s/nss_%s', path_to_folder, suffix);
			data_nss = importdata(path_nss);
			nss_avg = nss_avg + data_nss;
			
			path_eta = sprintf('%s/eta_%s', path_to_folder, suffix);
			data_eta = importdata(path_eta);
			eta_avg = eta_avg + data_eta;
            
            for n_id = 1: nn
            
				path_num_spikes = sprintf('%s/num_spikes_%d_%s', path_to_folder, (n_id - 1), suffix);
				data_num_spikes = importdata(path_num_spikes);
				num_spikes_avg(n_id) = num_spikes_avg(n_id) + data_num_spikes;
				
				path_f_out = sprintf('%s/f_out_%d_%s', path_to_folder, (n_id - 1), suffix);
				data_f_out = importdata(path_f_out);
				f_out_avg(n_id) = f_out_avg(n_id) + data_f_out;
				
				mean_f_out = mean_f_out + data_f_out;
		
			end
        end
		
        nss_avg = nss_avg / seed_num;
		eta_avg = eta_avg / seed_num;
		mean_f_out = mean_f_out / seed_num;
		mean_f_out = mean_f_out / nn;
		
		for n_id = 1: nn
			num_spikes_avg(n_id) = num_spikes_avg(n_id) / seed_num;
			f_out_avg(n_id) = f_out_avg(n_id) / seed_num;
		end
        
        result_data(str_num, 1) = y1_gamma;
		result_data(str_num, 2) = y2_gamma;
		
		for n_id = 1: nn
			result_data(str_num, 2 + n_id) = num_spikes_avg(n_id);
		end
		
		result_data(str_num, 2 + nn + 1) = nss_avg;
		result_data(str_num, 2 + nn + 2) = eta_avg;
		
		for n_id = 1: nn
			result_data(str_num, 4 + nn + n_id) = f_out_avg(n_id);
		end
		
		result_data(str_num, 4 + nn * 2 + 1) = mean_f_out;
		
		str_num = str_num + 1;
		
    end
end

fn_suffix = sprintf('system(%d)_gamma1(%0.4f)_gamma2(%0.4f)_fin(%0.4f)_b(%0.4f)_etaw(%0.4f)', ...
    sys_id, ...
	y1_gamma, ...
	y2_gamma, ...
	f_inv_start, ...
    b_start, ...
	eta_window);

file_name = sprintf('%s/gamma_exp_data_%s.txt', home_data_path, fn_suffix);
dlmwrite(file_name, result_data,'delimiter',' ');