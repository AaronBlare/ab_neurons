#include "config.h"

vector<string> split(const string& str, const string& delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;

	do
	{
		pos = str.find(delim, prev);

		if (pos == string::npos)
		{
			pos = str.length();
		}

		string token = str.substr(prev, pos - prev);

		if (!token.empty())
		{
			tokens.push_back(token);
		}

		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());

	return tokens;
}

void set_param(RunParam * rp, ConfigParam * cp, string str, string val)
{
	if (str.compare("system") == 0)
	{
		rp->system = atoi(val.c_str());
	}
	if (str.compare("task") == 0)
	{
		rp->task = atoi(val.c_str());
	}
	if (str.compare("path") == 0)
	{
		rp->path = val;
	}

	if (str.compare("f_in_start") == 0)
	{
		rp->f_in_start = atof(val.c_str());
	}
	if (str.compare("f_in_shift") == 0)
	{
		rp->f_in_shift = atof(val.c_str());
	}
	if (str.compare("f_in_num") == 0)
	{
		rp->f_in_num = atoi(val.c_str());
	}

	if (str.compare("b_start") == 0)
	{
		rp->b_start = atof(val.c_str());
	}
	if (str.compare("b_shift") == 0)
	{
		rp->b_shift = atof(val.c_str());
	}
	if (str.compare("b_num") == 0)
	{
		rp->b_num = atoi(val.c_str());
	}

	if (str.compare("seed_start") == 0)
	{
		rp->seed_start = atoi(val.c_str());
	}
	if (str.compare("seed_num") == 0)
	{
		rp->seed_num = atoi(val.c_str());
	}
	if (str.compare("max_num_seeds") == 0)
	{
		rp->max_num_seeds = atoi(val.c_str());
	}

	if (str.compare("nn") == 0)
	{
		cp->nn = atoi(val.c_str());
	}
	if (str.compare("ns") == 0)
	{
		cp->ns = atoi(val.c_str());
	}
	if (str.compare("nsps") == 0)
	{
		cp->nsps = atoi(val.c_str());
	}
	if (str.compare("ict") == 0)
	{
		cp->ict = atoi(val.c_str());
	}
	if (str.compare("nd") == 0)
	{
		cp->nd = atoi(val.c_str());
	}

	if (str.compare("thr_Vpost") == 0)
	{
		cp->thr_Vpost = atof(val.c_str());
	}

	if (str.compare("is_eta_calc") == 0)
	{
		cp->is_eta_calc = atoi(val.c_str());
	}
	if (str.compare("thr_eta") == 0)
	{
		cp->thr_eta = atof(val.c_str());
	}

	if (str.compare("e_1_alpha_x") == 0)
	{
		cp->e_1_alpha_x = atof(val.c_str());
	}
	if (str.compare("e_1_k_pre") == 0)
	{
		cp->e_1_k_pre = atof(val.c_str());
	}

	if (str.compare("e_1_k0") == 0)
	{
		cp->e_1_k0 = atof(val.c_str());
	}

	if (str.compare("e_1_2_tau") == 0)
	{
		cp->e_1_2_tau = atof(val.c_str());
	}

	if (str.compare("e_2_alpha_I") == 0)
	{
		cp->e_2_alpha_I = atof(val.c_str());
	}
	if (str.compare("e_2_A") == 0)
	{
		cp->e_2_A = atof(val.c_str());
	}

	if (str.compare("e_3_c") == 0)
	{
		cp->e_3_c = atof(val.c_str());
	}
	if (str.compare("e_3_g_Na") == 0)
	{
		cp->e_3_g_Na = atof(val.c_str());
	}
	if (str.compare("e_3_E_Na") == 0)
	{
		cp->e_3_E_Na = atof(val.c_str());
	}
	if (str.compare("e_3_g_K") == 0)
	{
		cp->e_3_g_K = atof(val.c_str());
	}
	if (str.compare("e_3_E_K") == 0)
	{
		cp->e_3_E_K = atof(val.c_str());
	}
	if (str.compare("e_3_g_l") == 0)
	{
		cp->e_3_g_l = atof(val.c_str());
	}
	if (str.compare("e_3_E_l") == 0)
	{
		cp->e_3_E_l = atof(val.c_str());
	}
	if (str.compare("e_3_I_th") == 0)
	{
		cp->e_3_I_th = atof(val.c_str());
	}
	if (str.compare("e_3_theta_x") == 0)
	{
		cp->e_3_theta_x = atof(val.c_str());
	}
	if (str.compare("e_3_k_x") == 0)
	{
		cp->e_3_k_x = atof(val.c_str());
	}

	if (str.compare("e_4_alpha_a1") == 0)
	{
		cp->e_4_alpha_a1 = atof(val.c_str());
	}
	if (str.compare("e_4_alpha_a2") == 0)
	{
		cp->e_4_alpha_a2 = atof(val.c_str());
	}
	if (str.compare("e_4_alpha_a3") == 0)
	{
		cp->e_4_alpha_a3 = atof(val.c_str());
	}
	if (str.compare("e_4_beta_b1") == 0)
	{
		cp->e_4_beta_b1 = atof(val.c_str());
	}
	if (str.compare("e_4_beta_b2") == 0)
	{
		cp->e_4_beta_b2 = atof(val.c_str());
	}
	if (str.compare("e_4_beta_b3") == 0)
	{
		cp->e_4_beta_b3 = atof(val.c_str());
	}

	if (str.compare("e_5_alpha_a1") == 0)
	{
		cp->e_5_alpha_a1 = atof(val.c_str());
	}
	if (str.compare("e_5_alpha_a2") == 0)
	{
		cp->e_5_alpha_a2 = atof(val.c_str());
	}
	if (str.compare("e_5_beta_b1") == 0)
	{
		cp->e_5_beta_b1 = atof(val.c_str());
	}
	if (str.compare("e_5_beta_b2") == 0)
	{
		cp->e_5_beta_b2 = atof(val.c_str());
	}
	if (str.compare("e_5_beta_b3") == 0)
	{
		cp->e_5_beta_b3 = atof(val.c_str());
	}

	if (str.compare("e_6_alpha_a1") == 0)
	{
		cp->e_6_alpha_a1 = atof(val.c_str());
	}
	if (str.compare("e_6_alpha_a2") == 0)
	{
		cp->e_6_alpha_a2 = atof(val.c_str());
	}
	if (str.compare("e_6_alpha_a3") == 0)
	{
		cp->e_6_alpha_a3 = atof(val.c_str());
	}
	if (str.compare("e_6_beta_b1") == 0)
	{
		cp->e_6_beta_b1 = atof(val.c_str());
	}
	if (str.compare("e_6_beta_b2") == 0)
	{
		cp->e_6_beta_b2 = atof(val.c_str());
	}

	if (str.compare("e_y1_alpha") == 0)
	{
		cp->e_y1_alpha = atof(val.c_str());
	}
	if (str.compare("e_y1_theta") == 0)
	{
		cp->e_y1_theta = atof(val.c_str());
	}
	if (str.compare("e_y1_k") == 0)
	{
		cp->e_y1_k = atof(val.c_str());
	}
	if (str.compare("e_y1_gamma") == 0)
	{
		cp->e_y1_gamma = atof(val.c_str());
	}

	if (str.compare("e_y2_alpha") == 0)
	{
		cp->e_y2_alpha = atof(val.c_str());
	}
	if (str.compare("e_y2_theta") == 0)
	{
		cp->e_y2_theta = atof(val.c_str());
	}
	if (str.compare("e_y2_k") == 0)
	{
		cp->e_y2_k = atof(val.c_str());
	}
	if (str.compare("e_y2_gamma") == 0)
	{
		cp->e_y2_gamma = atof(val.c_str());
	}
}

void init_params(RunParam * rp, ConfigParam * cp, char * file_name)
{
	string line;
	ifstream config_file(file_name);
	if (config_file.is_open())
	{
		while (getline(config_file, line))
		{
			vector<string> tokens = split(line, " ");

			if (tokens.size() == 2)
			{
				set_param(rp, cp, tokens[0], tokens[1]);
			}
		}
		config_file.close();
	}
	else
	{
		cout << "Unable to open file" << endl;
		cout << "Init with default params" << endl;
	}

	output_params(rp, cp);
}

void output_params(RunParam * rp, ConfigParam * cp)
{
	cout << "############# parameters #############" << endl;

	cout << "system = " << rp->system << endl;
	cout << "task = " << rp->task << endl;

	cout << "path = " << rp->path << endl;

	cout << "f_in_start = " << rp->f_in_start << endl;
	cout << "f_in_shift = " << rp->f_in_shift << endl;
	cout << "f_in_num = " << rp->f_in_num << endl;

	cout << "b_start = " << rp->b_start << endl;
	cout << "b_shift = " << rp->b_shift << endl;
	cout << "b_num = " << rp->b_num << endl;

	cout << "seed_start = " << rp->seed_start << endl;
	cout << "seed_num = " << rp->seed_num << endl;
	cout << "max_num_seeds = " << rp->max_num_seeds << endl;

	cout << "nn = " << cp->nn << endl;

	cout << "ns = " << cp->ns << endl;
	cout << "nsps = " << cp->nsps << endl;
	cout << "ict = " << cp->ict << endl;
	cout << "nd = " << cp->nd << endl;

	cout << "thr_Vpost = " << cp->thr_Vpost << endl;

	cout << "is_eta_calc = " << cp->is_eta_calc << endl;
	cout << "thr_eta = " << cp->thr_eta << endl;

	cout << "e_1_alpha_x = " << cp->e_1_alpha_x << endl;
	cout << "e_1_k_pre = " << cp->e_1_k_pre << endl;

	cout << "e_1_k0 = " << cp->e_1_k0 << endl;

	cout << "e_1_2_tau = " << cp->e_1_2_tau << endl;
	
	cout << "e_2_alpha_I = " << cp->e_2_alpha_I << endl;
	cout << "e_2_A = " << cp->e_2_A << endl;

	cout << "e_3_c = " << cp->e_3_c << endl;
	cout << "e_3_g_Na = " << cp->e_3_g_Na << endl;
	cout << "e_3_E_Na = " << cp->e_3_E_Na << endl;
	cout << "e_3_g_K = " << cp->e_3_g_K << endl;
	cout << "e_3_E_K = " << cp->e_3_E_K << endl;
	cout << "e_3_g_l = " << cp->e_3_g_l << endl;
	cout << "e_3_E_l = " << cp->e_3_E_l << endl;
	cout << "e_3_I_th = " << cp->e_3_I_th << endl;
	cout << "e_3_theta_x = " << cp->e_3_theta_x << endl;
	cout << "e_3_k_x = " << cp->e_3_k_x << endl;

	cout << "e_4_alpha_a1 = " << cp->e_4_alpha_a1 << endl;
	cout << "e_4_alpha_a2 = " << cp->e_4_alpha_a2 << endl;
	cout << "e_4_alpha_a3 = " << cp->e_4_alpha_a3 << endl;
	cout << "e_4_beta_b1 = " << cp->e_4_beta_b1 << endl;
	cout << "e_4_beta_b2 = " << cp->e_4_beta_b2 << endl;
	cout << "e_4_beta_b3 = " << cp->e_4_beta_b3 << endl;

	cout << "e_5_alpha_a1 = " << cp->e_5_alpha_a1 << endl;
	cout << "e_5_alpha_a2 = " << cp->e_5_alpha_a2 << endl;
	cout << "e_5_beta_b1 = " << cp->e_5_beta_b1 << endl;
	cout << "e_5_beta_b2 = " << cp->e_5_beta_b2 << endl;
	cout << "e_5_beta_b3 = " << cp->e_5_beta_b3 << endl;

	cout << "e_6_alpha_a1 = " << cp->e_6_alpha_a1 << endl;
	cout << "e_6_alpha_a2 = " << cp->e_6_alpha_a2 << endl;
	cout << "e_6_alpha_a3 = " << cp->e_6_alpha_a3 << endl;
	cout << "e_6_beta_b1 = " << cp->e_6_beta_b1 << endl;
	cout << "e_6_beta_b2 = " << cp->e_6_beta_b2 << endl;

	cout << "e_y1_alpha = " << cp->e_y1_alpha << endl;
	cout << "e_y1_theta = " << cp->e_y1_theta << endl;
	cout << "e_y1_k = " << cp->e_y1_k << endl;
	cout << "e_y1_gamma = " << cp->e_y1_gamma << endl;

	cout << "e_y2_alpha = " << cp->e_y2_alpha << endl;
	cout << "e_y2_theta = " << cp->e_y2_theta << endl;
	cout << "e_y2_k = " << cp->e_y2_k << endl;
	cout << "e_y2_gamma = " << cp->e_y2_gamma << endl;

	cout << "######################################" << endl;
}