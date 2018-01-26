use File::Copy;
use Data::Dumper;
use Cwd;
use Math::Trig;
use POSIX;
$dir = getcwd;

$data_path = "/data/biophys/yusipov/ab_neurons";

$PI = 3.1415926535897932384626433832795;

for($f_in_Hz = 1.0; $f_in_Hz <= 1000.01; $f_in_Hz += 1.0)
{
	print "f_in_Hz = $f_in_Hz\n";
	
	$val = 1000.0 / $f_in_Hz;
	
	$sys_id = 1;
	$task = 1;
	$path = "";
	$f_in_start = $val;
	$f_in_shift = 1.0;
	$f_in_num = 1;
	$b_start = 5.0;
	$b_shift = 1.0;
	$b_num = 1;
	$seed_start = 0;
	$seed_num = 1;
	$max_num_seeds = 1000000;
	$ns = 5400000;
	$nsps  = 1000;
	$nd = 10;
	$thr_Vpost = 0.0;
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
	$e_3_I_th = 5.5;
	$e_3_theta_x = 0.2;
	$e_3_k_x = 0.05;
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
	$e_y1_theta = 0.3;
	$e_y1_k = 0.1;
	$e_y1_gamma = -0.8;
	$e_y2_alpha = 0.01;
	$e_y2_theta = 0.3;
	$e_y2_k = 0.1;
	$e_y2_gamma = 0.4;
	
	
	$f_in_str = sprintf("%.4f", $f_in_start);
	$b_str = sprintf("%.4f", $b_start);
	$thr_Vpost_str = sprintf("%.4f", $thr_Vpost);
		
	$start = 1;
	$finish = 2;
	%exp = ();
	$i = 0;
	$i = $start;
	
	sub ForderName{
		$key_str = $_[0];
		
		return  "$data_path/system_${sys_id}/task_${task}/ns_${ns}/nsps_${nsps}/f_in_${f_in_str}/b_${b_str}/thr_Vpost_${thr_Vpost_str}/seed_${key_str}";
	}
	
	mkdir "$data_path/system_${sys_id}";
	mkdir "$data_path/system_${sys_id}/task_${task}";
	mkdir "$data_path/system_${sys_id}/task_${task}/ns_${ns}";
	mkdir "$data_path/system_${sys_id}/task_${task}/ns_${ns}/nsps_${nsps}";
	mkdir "$data_path/system_${sys_id}/task_${task}/ns_${ns}/nsps_${nsps}/f_in_${f_in_str}";
	mkdir "$data_path/system_${sys_id}/task_${task}/ns_${ns}/nsps_${nsps}/f_in_${f_in_str}/b_${b_str}";
	mkdir "$data_path/system_${sys_id}/task_${task}/ns_${ns}/nsps_${nsps}/f_in_${f_in_str}/b_${b_str}/thr_Vpost_${thr_Vpost_str}";

	for($val = $start; $val < $finish; $val+=1)
	{
		$exp{ForderName($i)} = $val;
		$i++;
	}

	for($i = $start; $i < $finish; $i++)
	{
		$key = ForderName($i);    
		mkdir "$key";
		
		$seed_start = $i;
			
		print "$seed_start \n";
		
		open( WF,">$key/config.txt");
		
		print WF "system $sys_id \n"; 
		print WF "task $task \n"; 
		print WF "path $path \n"; 
		print WF "f_in_start $f_in_start \n"; 
		print WF "f_in_shift $f_in_shift \n"; 
		print WF "f_in_num $f_in_num \n"; 
		print WF "b_start $b_start \n"; 
		print WF "b_shift $b_shift \n"; 
		print WF "b_num $b_num \n"; 
		print WF "seed_start $i \n"; 
		print WF "seed_num $seed_num \n"; 
		print WF "max_num_seeds $max_num_seeds \n"; 
		print WF "ns $ns \n"; 
		print WF "nsps $nsps \n";
		print WF "nd $nd \n"; 
		print WF "thr_Vpost $thr_Vpost \n"; 
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

		$test_file = sprintf('%s/f_out_fin(%0.4f)_b(%0.4f)_seed(%d).txt', $key, $f_in_start, $b_start, $i);
			
		unless (-e "$test_file")
		{	
			print "qsub -wd $dir run_1_thread.sh $key \n";
			system "qsub -wd $dir run_1_thread.sh $key";
		}
	}
}
