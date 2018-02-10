#include "rightparter.h"

void SimpleRightPartBehaviour::right_part(ConfigParam * cp, MainData * md, int sub_step, double * impulses) const
{
	right_part_common(cp, md, sub_step, impulses);
}

void SimpleRightPartBehaviour::update_arg(ConfigParam * cp, MainData * md, int sub_step, double coeff) const
{
	update_arg_common(cp, md, sub_step, coeff);
}

void SimpleRightPartBehaviour::rk_final(ConfigParam * cp, MainData * md, double step) const
{
	rk_final_common(cp, md, step);
}

void SimpleRightPartBehaviour::set_init_args(ConfigParam * cp, MainData * md) const
{
	set_init_args_common(cp, md);
}

void FullRightPartBehaviour::right_part(ConfigParam * cp, MainData * md, int sub_step, double * impulses) const
{
	right_part_common(cp, md, sub_step, impulses);
}

void FullRightPartBehaviour::update_arg(ConfigParam * cp, MainData * md, int sub_step, double coeff) const
{
	update_arg_common(cp, md, sub_step, coeff);
}

void FullRightPartBehaviour::rk_final(ConfigParam * cp, MainData * md, double step) const
{
	rk_final_common(cp, md, step);
}

void FullRightPartBehaviour::set_init_args(ConfigParam * cp, MainData * md) const
{
	set_init_args_common(cp, md);
}

void right_part_common(ConfigParam * cp, MainData * md, int sub_step, double * impulses)
{
	double time = md->time;

	double * x_env;
	double * ks_env;
	if (md->size_env > 0)
	{
		x_env = md->args_env;
		if (sub_step == 1)
		{
			ks_env = md->k1s_env;
		}
		else if (sub_step == 2)
		{
			ks_env = md->k2s_env;
		}
		else if (sub_step == 3)
		{
			ks_env = md->k3s_env;
		}
		else if (sub_step == 4)
		{
			ks_env = md->k4s_env;
		}
	}

	if (md->size_env > 0)
	{
		double x_neu_sum = 0.0;
		for (int n_id = 0; n_id < cp->nn; n_id++)
		{
			x_neu_sum += md->args_neu[n_id][0];
		}

		double y1_H = 1.0 / (1.0 + exp(-(x_neu_sum - cp->e_y1_theta) / cp->e_y1_k));
		ks_env[0] = -cp->e_y1_alpha * (x_env[0] - y1_H);

		double y2_H = 1.0 / (1.0 + exp(-(x_neu_sum - cp->e_y2_theta) / cp->e_y2_k));
		ks_env[1] = -cp->e_y2_alpha * (x_env[1] - y2_H);
	}

	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		double impulse = impulses[n_id];

		double * x_neu = md->args_neu[n_id];
		double * ks_neu;
		if (sub_step == 1)
		{
			ks_neu = md->k1s_neu[n_id];
		}
		else if (sub_step == 2)
		{
			ks_neu = md->k2s_neu[n_id];
		}
		else if (sub_step == 3)
		{
			ks_neu = md->k3s_neu[n_id];
		}
		else if (sub_step == 4)
		{
			ks_neu = md->k4s_neu[n_id];
		}

		if (md->size_env > 0)
		{
			ks_neu[0] = -(cp->e_1_alpha_x) * (x_neu[0] - (cp->e_1_k0) * (1.0 + cp->e_y1_gamma * x_env[0]) * impulse);
		}
		else
		{
			ks_neu[0] = -(cp->e_1_alpha_x) * (x_neu[0] - (cp->e_1_k0) * impulse);
		}

		ks_neu[1] = (cp->e_2_alpha_I) * (-x_neu[1] - (md->A[n_id]) * impulse);

		double I_Na = cp->e_3_g_Na * std::pow(x_neu[4], 3.0) * x_neu[5] * (x_neu[2] - cp->e_3_E_Na);
		double I_K = cp->e_3_g_K * std::pow(x_neu[3], 4.0) * (x_neu[2] - cp->e_3_E_K);
		double I_leak = cp->e_3_g_l * (x_neu[2] - cp->e_3_E_l);
		double I_mem = I_Na + I_K + I_leak;
		double I_th = cp->e_3_I_th;
		double I_syn = x_neu[1] / (1.0 + exp(-(x_neu[0] - cp->e_3_theta_x) / cp->e_3_k_x));
		ks_neu[2] = (I_th - I_mem - I_syn) / cp->e_3_c;

		double alpha_n = cp->e_4_alpha_a1 * (x_neu[2] + cp->e_4_alpha_a2) / (1.0 - exp(cp->e_4_alpha_a3 * (-cp->e_4_alpha_a2 - x_neu[2])));
		double beta_n = cp->e_4_beta_b1 * exp((-x_neu[2] - cp->e_4_beta_b2) / (cp->e_4_beta_b3));
		ks_neu[3] = alpha_n * (1.0 - x_neu[3]) - beta_n * x_neu[3];

		double alpha_m = cp->e_5_alpha_a1 * (x_neu[2] + cp->e_5_alpha_a2) / (1.0 - exp(cp->e_5_alpha_a1 * (-cp->e_5_alpha_a2 - x_neu[2])));
		double beta_m = cp->e_5_beta_b1 * exp((-x_neu[2] - cp->e_5_beta_b2) / (cp->e_5_beta_b3));
		ks_neu[4] = alpha_m * (1.0 - x_neu[4]) - beta_m * x_neu[4];

		double alpha_h = cp->e_6_alpha_a1 * exp(cp->e_6_alpha_a2 * (-x_neu[2] - cp->e_6_alpha_a3));
		double beta_h = 1.0 / (1.0 + exp(cp->e_6_beta_b1 * (-cp->e_6_beta_b2 - x_neu[2])));
		ks_neu[5] = alpha_h * (1.0 - x_neu[5]) - beta_h * x_neu[5];
	}
}

void update_arg_common(ConfigParam * cp, MainData * md, int sub_step, double coeff)
{
	double * x_env;
	double * args_env;
	double * ks_env;
	if (md->size_env > 0)
	{
		x_env = md->data_env;
		args_env = md->args_env;
		if (sub_step == 1)
		{
			ks_env = md->k1s_env;
		}
		else if (sub_step == 2)
		{
			ks_env = md->k2s_env;
		}
		else if (sub_step == 3)
		{
			ks_env = md->k3s_env;
		}
		else if (sub_step == 4)
		{
			ks_env = md->k4s_env;
		}
	}

	if (md->size_env > 0)
	{
		for (int eq_id = 0; eq_id < md->size_env; eq_id++)
		{
			args_env[eq_id] = x_env[eq_id] + coeff * ks_env[eq_id];
		}
	}

	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		double * x_neu = md->data_neu[n_id];
		double * args_neu = md->args_neu[n_id];
		double * ks_neu;
		if (sub_step == 1)
		{
			ks_neu = md->k1s_neu[n_id];
		}
		else if (sub_step == 2)
		{
			ks_neu = md->k2s_neu[n_id];
		}
		else if (sub_step == 3)
		{
			ks_neu = md->k3s_neu[n_id];
		}
		else if (sub_step == 4)
		{
			ks_neu = md->k4s_neu[n_id];
		}

		for (int eq_id = 0; eq_id < md->size_neu; eq_id++)
		{
			args_neu[eq_id] = x_neu[eq_id] + coeff * ks_neu[eq_id];
		}
	}
}

void rk_final_common(ConfigParam * cp, MainData * md, double step)
{
	double * x_env;
	if (md->size_env > 0)
	{
		x_env = md->data_env;
	}

	if (md->size_env > 0)
	{
		for (int eq_id = 0; eq_id < md->size_env; eq_id++)
		{
			x_env[eq_id] += (md->k1s_env[eq_id] + 2.0 * md->k2s_env[eq_id] + 2.0 * md->k3s_env[eq_id] + md->k4s_env[eq_id]) * step / 6.0;
		}
	}

	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		double * x_neu = md->data_neu[n_id];

		for (int eq_id = 0; eq_id < md->size_neu; eq_id++)
		{
			x_neu[eq_id] += (md->k1s_neu[n_id][eq_id] + 2.0 * md->k2s_neu[n_id][eq_id] + 2.0 * md->k3s_neu[n_id][eq_id] + md->k4s_neu[n_id][eq_id]) * step / 6.0;
		}
	}
}

void set_init_args_common(ConfigParam * cp, MainData * md)
{
	double * x_env;
	double * args_env;
	if (md->size_env > 0)
	{
		x_env = md->data_env;
		args_env = md->args_env;
	}

	if (md->size_env > 0)
	{
		for (int eq_id = 0; eq_id < md->size_env; eq_id++)
		{
			args_env[eq_id] = x_env[eq_id];
		}
	}

	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		double * x_neu = md->data_neu[n_id];
		double * args_neu = md->args_neu[n_id];

		for (int eq_id = 0; eq_id < md->size_neu; eq_id++)
		{
			args_neu[eq_id] = x_neu[eq_id];
		}
	}
}