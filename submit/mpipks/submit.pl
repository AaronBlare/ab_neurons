use File::Copy;
use Data::Dumper;
use Cwd;
use Math::Trig;
use POSIX;
$dir = getcwd;

$data_path = "/data/biophys/yusipov/ab_neurons/gamma_1_from_gamma_2";

$PI = 3.1415926535897932384626433832795;

for($gamma_1_curr = 0.0; $gamma_1_curr <= 0.000001; $gamma_1_curr += 0.2)
{
	for($gamma_2_curr = 0.0; $gamma_2_curr <= 5.000001; $gamma_2_curr += 0.2)
	{
		for($b_curr = 2.0; $b_curr <= 2.000001; $b_curr += 2.0)
		{
			for($f_in_Hz = 1.0; $f_in_Hz <= 1.00001; $f_in_Hz += 50.0)
			{
				print "f_in_Hz = $f_in_Hz\n";
				
				#$val = 1000.0 / $f_in_Hz;
				
				$val = 2;
				
				$f_in_0 = $val;
				$f_in_1 = $val;

				$sys_id = 1;
				$task = 1;
				$path = "";
				$b_start = $b_curr;
				$b_shift = 1.0;
				$b_num = 1;
				$seed_start = 0;
				$seed_num = 1;
				$max_num_seeds = 1000000;
				$nn = 2;
				$ns = 600000;
				$nsps  = 1000;
				$nd = 1;
				$thr_Vpost = 0.0;
				$is_eta_calc = 1;
				$thr_eta = -40.0;
				$eta_window = 8.0;
				$is_spikes_save = 0;
				$e_1_alpha_x =  0.1;
				$e_1_k_pre = 2.0;
				$e_1_k0 = 2.0;
				$e_1_2_tau = 1.0;
				$e_2_alpha_I = 0.1;
				$e_2_A = 5.0;
				$e_3_c = 1.0;
				$e_3_g_Na = 120.0;
				$e_3_E_Na = 50.0;
				$e_3_g_K = 36.0;
				$e_3_E_K = -77.0;
				$e_3_g_l = 0.3;
				$e_3_E_l = -54.4;
				$e_3_I_th = 5.7;
				$e_3_theta_x = 1.2;
				$e_3_k_x = 0.01;
				$e_4_alpha_a1 = 0.01;
				$e_4_alpha_a2 = 55.0;
				$e_4_alpha_a3 = 0.1;
				$e_4_beta_b1 = 0.125;
				$e_4_beta_b2 = 65.0;
				$e_4_beta_b3 = 80.0;
				$e_5_alpha_a1 = 0.1;
				$e_5_alpha_a2 = 40.0;
				$e_5_beta_b1 = 4.0;
				$e_5_beta_b2 = 65.0;
				$e_5_beta_b3 = 18.0;
				$e_6_alpha_a1 = 0.07;
				$e_6_alpha_a2 = 0.05;
				$e_6_alpha_a3 = 65.0;
				$e_6_beta_b1 = 0.1;
				$e_6_beta_b2 = 35.0;
				$e_y1_alpha = 0.01;
				$e_y1_theta = 1.2;
				$e_y1_k = 0.1;
				$e_y1_gamma = $gamma_1_curr;
				$e_y2_alpha = 0.01;
				$e_y2_theta = 1.2;
				$e_y2_k = 0.1;
				$e_y2_gamma = $gamma_2_curr;
				
				$e_y1_gamma_str = sprintf("%.4f", $e_y1_gamma);
				$e_y2_gamma_str = sprintf("%.4f", $e_y2_gamma);
				$f_in_str = sprintf("%.4f", $f_in_0);
				$b_str = sprintf("%.4f", $b_start);
				$thr_Vpost_str = sprintf("%.4f", $thr_Vpost);
				$thr_eta_str = sprintf("%.4f", $thr_eta);
				$eta_window_str = sprintf("%.4f", $eta_window);
					
				$start = 0;
				$finish = 20;
				%exp = ();
				$i = $start;
				
				$ss_begin = $start * $nn;
				$ss_end = $finish * $nn;
				$ss_step = $nn;
				
				sub ForderName{
					$key_str = $_[0];
					
					return  "$data_path/system_${sys_id}/task_${task}/nn_${nn}/ns_${ns}/nsps_${nsps}/y1_gamma_${e_y1_gamma_str}/y2_gamma_${e_y2_gamma_str}/f_in_${f_in_str}/b_${b_str}/thr_Vpost_${thr_Vpost_str}/eta_${eta_window_str}/seed_${key_str}";
				}
				
				mkdir "$data_path/system_${sys_id}";
				mkdir "$data_path/system_${sys_id}/task_${task}";
				mkdir "$data_path/system_${sys_id}/task_${task}/nn_${nn}";
				mkdir "$data_path/system_${sys_id}/task_${task}/nn_${nn}/ns_${ns}";
				mkdir "$data_path/system_${sys_id}/task_${task}/nn_${nn}/ns_${ns}/nsps_${nsps}";
				mkdir "$data_path/system_${sys_id}/task_${task}/nn_${nn}/ns_${ns}/nsps_${nsps}/y1_gamma_${e_y1_gamma_str}";
				mkdir "$data_path/system_${sys_id}/task_${task}/nn_${nn}/ns_${ns}/nsps_${nsps}/y1_gamma_${e_y1_gamma_str}/y2_gamma_${e_y2_gamma_str}";
				mkdir "$data_path/system_${sys_id}/task_${task}/nn_${nn}/ns_${ns}/nsps_${nsps}/y1_gamma_${e_y1_gamma_str}/y2_gamma_${e_y2_gamma_str}/f_in_${f_in_str}";
				mkdir "$data_path/system_${sys_id}/task_${task}/nn_${nn}/ns_${ns}/nsps_${nsps}/y1_gamma_${e_y1_gamma_str}/y2_gamma_${e_y2_gamma_str}/f_in_${f_in_str}/b_${b_str}";
				mkdir "$data_path/system_${sys_id}/task_${task}/nn_${nn}/ns_${ns}/nsps_${nsps}/y1_gamma_${e_y1_gamma_str}/y2_gamma_${e_y2_gamma_str}/f_in_${f_in_str}/b_${b_str}/thr_Vpost_${thr_Vpost_str}";
				mkdir "$data_path/system_${sys_id}/task_${task}/nn_${nn}/ns_${ns}/nsps_${nsps}/y1_gamma_${e_y1_gamma_str}/y2_gamma_${e_y2_gamma_str}/f_in_${f_in_str}/b_${b_str}/thr_Vpost_${thr_Vpost_str}/eta_${eta_window_str}";
				
				for($val = $ss_begin; $val < $ss_end; $val += $ss_step)
				{
					$exp{ForderName($i)} = $val;
					$i++;
				}

				for($i = $ss_begin; $i < $ss_end; $i += $ss_step)
				{
					$key = ForderName($i);    
					mkdir "$key";
					
					$seed_start = $i;
						
					print "$seed_start \n";
					
					open( WF,">$key/config.txt");	
					print WF "system $sys_id \n"; 
					print WF "task $task \n"; 
					print WF "path $path \n"; 
					print WF "b_start $b_start \n"; 
					print WF "b_shift $b_shift \n"; 
					print WF "b_num $b_num \n"; 
					print WF "seed_start $i \n"; 
					print WF "seed_num $seed_num \n"; 
					print WF "max_num_seeds $max_num_seeds \n"; 
					print WF "nn $nn \n"; 
					print WF "ns $ns \n"; 
					print WF "nsps $nsps \n";
					print WF "nd $nd \n"; 
					print WF "thr_Vpost $thr_Vpost \n";
					print WF "is_eta_calc $is_eta_calc \n"; 
					print WF "thr_eta $thr_eta \n"; 
					print WF "eta_window $eta_window \n"; 
					print WF "is_spikes_save $is_spikes_save \n";
					print WF "e_1_alpha_x $e_1_alpha_x \n"; 
					print WF "e_1_k_pre $e_1_k_pre \n";
					print WF "e_1_k0 $e_1_k0 \n"; 
					print WF "e_1_2_tau $e_1_2_tau \n"; 
					print WF "e_2_alpha_I $e_2_alpha_I \n"; 
					print WF "e_2_A $e_2_A \n"; 
					print WF "e_3_c $e_3_c \n"; 
					print WF "e_3_g_Na $e_3_g_Na \n"; 
					print WF "e_3_E_Na $e_3_E_Na \n"; 
					print WF "e_3_g_K $e_3_g_K \n"; 
					print WF "e_3_E_K $e_3_E_K \n"; 
					print WF "e_3_g_l $e_3_g_l \n"; 
					print WF "e_3_E_l $e_3_E_l \n"; 
					print WF "e_3_I_th $e_3_I_th \n";
					print WF "e_3_theta_x $e_3_theta_x \n";
					print WF "e_3_k_x $e_3_k_x \n";
					print WF "e_4_alpha_a1 $e_4_alpha_a1 \n";
					print WF "e_4_alpha_a2 $e_4_alpha_a2 \n";
					print WF "e_4_alpha_a3 $e_4_alpha_a3 \n";
					print WF "e_4_beta_b1 $e_4_beta_b1 \n";
					print WF "e_4_beta_b2 $e_4_beta_b2 \n";
					print WF "e_4_beta_b3 $e_4_beta_b3 \n";
					print WF "e_5_alpha_a1 $e_5_alpha_a1 \n";
					print WF "e_5_alpha_a2 $e_5_alpha_a2 \n";
					print WF "e_5_beta_b1 $e_5_beta_b1 \n";
					print WF "e_5_beta_b2 $e_5_beta_b2 \n";
					print WF "e_5_beta_b3 $e_5_beta_b3 \n";
					print WF "e_6_alpha_a1 $e_6_alpha_a1 \n";
					print WF "e_6_alpha_a2 $e_6_alpha_a2 \n";
					print WF "e_6_alpha_a3 $e_6_alpha_a3 \n";
					print WF "e_6_beta_b1 $e_6_beta_b1 \n";
					print WF "e_6_beta_b2 $e_6_beta_b2 \n";
					print WF "e_y1_alpha $e_y1_alpha \n";
					print WF "e_y1_theta $e_y1_theta \n";
					print WF "e_y1_k $e_y1_k \n";
					print WF "e_y1_gamma $e_y1_gamma \n";
					print WF "e_y2_alpha $e_y2_alpha \n";
					print WF "e_y2_theta $e_y2_theta \n";
					print WF "e_y2_k $e_y2_k \n";
					print WF "e_y2_gamma $e_y2_gamma \n";
					close WF;
					
					open( WF,">$key/fin.txt"); 
					print WF "$f_in_0 \n"; 
					print WF "$f_in_1 \n";
					close WF;

					$test_file = sprintf('%s/f_out_0_fin(%0.4f)_b(%0.4f)_seed(%d).txt', $key, $f_in_0, $b_start, $i);
						
					unless (-e "$test_file")
					{	
						print "qsub -wd $dir run_1_thread.sh $key \n";
						system "qsub -wd $dir run_1_thread.sh $key";
					}
				}
			}
		}
	}
}