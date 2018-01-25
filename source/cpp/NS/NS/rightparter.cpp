#include "rightparter.h"

void SimpleRightPartBehaviour::set_right_part() const
{
	right_part = &right_part_simple;
}

void FullRightPartBehaviour::set_right_part() const
{
	right_part = &right_part_full;
}

void right_part_simple(ConfigParam * cp, MainData * md, double * ks, double * x, double time, double impulse)
{
	ks[0] = -(cp->e_1_alpha_x) * (x[0] - (cp->e_1_k_pre) * impulse);

	ks[1] = (cp->e_2_alpha_I) * (-x[1] - (md->A) * impulse);

	double I_Na = cp->e_3_g_Na * std::pow(x[4], 3.0) * x[5] * (x[2] - cp->e_3_E_Na);
	double I_K = cp->e_3_g_K * std::pow(x[3], 4.0) * (x[2] - cp->e_3_E_K);
	double I_leak = cp->e_3_g_l * (x[2] - cp->e_3_E_l);
	double I_mem = I_Na + I_K + I_leak;
	double I_th = cp->e_3_I_th;
	double I_syn = x[1] / (1.0 + exp(-(x[0] - cp->e_3_theta_x) / cp->e_3_k_x));
	ks[2] = (I_th - I_mem - I_syn) / cp->e_3_c;

	double alpha_n = cp->e_4_alpha_a1 * (x[2] + cp->e_4_alpha_a2) / (1.0 - exp(cp->e_4_alpha_a3 * (-cp->e_4_alpha_a2 - x[2])));
	double beta_n = cp->e_4_beta_b1 * exp((-x[2] - cp->e_4_beta_b2) / (cp->e_4_beta_b3));
	ks[3] = alpha_n * (1.0 - x[3]) - beta_n * x[3];

	double alpha_m = cp->e_5_alpha_a1 * (x[2] + cp->e_5_alpha_a2) / (1.0 - exp(cp->e_5_alpha_a1 * (-cp->e_5_alpha_a2 - x[2])));
	double beta_m = cp->e_5_beta_b1 * exp((-x[2] - cp->e_5_beta_b2) / (cp->e_5_beta_b3));
	ks[4] = alpha_m * (1.0 - x[4]) - beta_m * x[4];

	double alpha_h = cp->e_6_alpha_a1 * exp(cp->e_6_alpha_a2 * (-x[2] - cp->e_6_alpha_a3));
	double beta_h = 1.0 / (1.0 + exp(cp->e_6_beta_b1 * (-cp->e_6_beta_b2 - x[2])));
	ks[5] = alpha_h * (1.0 - x[5]) - beta_h * x[5];
}

void right_part_full(ConfigParam * cp, MainData * md, double * ks, double * x, double time, double impulse)
{
	ks[0] = -(cp->e_1_alpha_x) * (x[0] - (cp->e_1_k0) * (1.0 + cp->e_y1_gamma * x[6]) * impulse);

	ks[1] = (cp->e_2_alpha_I) * (-x[1] - (md->A) * impulse);

	double I_Na = cp->e_3_g_Na * std::pow(x[4], 3.0) * x[5] * (x[2] - cp->e_3_E_Na);
	double I_K = cp->e_3_g_K * std::pow(x[3], 4.0) * (x[2] - cp->e_3_E_K);
	double I_leak = cp->e_3_g_l * (x[2] - cp->e_3_E_l);
	double I_mem = I_Na + I_K + I_leak;
	double I_th = cp->e_3_I_th;
	double I_syn = x[1] / (1.0 + exp(-(x[0] - cp->e_3_theta_x) / cp->e_3_k_x));
	ks[2] = (I_th - I_mem - I_syn) / cp->e_3_c;

	double alpha_n = cp->e_4_alpha_a1 * (x[2] + cp->e_4_alpha_a2) / (1.0 - exp(cp->e_4_alpha_a3 * (-cp->e_4_alpha_a2 - x[2])));
	double beta_n = cp->e_4_beta_b1 * exp((-x[2] - cp->e_4_beta_b2) / (cp->e_4_beta_b3));
	ks[3] = alpha_n * (1.0 - x[3]) - beta_n * x[3];

	double alpha_m = cp->e_5_alpha_a1 * (x[2] + cp->e_5_alpha_a2) / (1.0 - exp(cp->e_5_alpha_a1 * (-cp->e_5_alpha_a2 - x[2])));
	double beta_m = cp->e_5_beta_b1 * exp((-x[2] - cp->e_5_beta_b2) / (cp->e_5_beta_b3));
	ks[4] = alpha_m * (1.0 - x[4]) - beta_m * x[4];

	double alpha_h = cp->e_6_alpha_a1 * exp(cp->e_6_alpha_a2 * (-x[2] - cp->e_6_alpha_a3));
	double beta_h = 1.0 / (1.0 + exp(cp->e_6_beta_b1 * (-cp->e_6_beta_b2 - x[2])));
	ks[5] = alpha_h * (1.0 - x[5]) - beta_h * x[5];

	double y1_H = 1.0 / (1.0 + exp(-(x[0] - cp->e_y1_theta) / cp->e_y1_k));
	ks[6] = -cp->e_y1_alpha * (x[6] - y1_H);

	double y2_H = 1.0 / (1.0 + exp(-(x[0] - cp->e_y2_theta) / cp->e_y2_k));
	ks[7] = -cp->e_y2_alpha * (x[7] - y2_H);
}


