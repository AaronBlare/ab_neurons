#pragma once
#include "config.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <complex>
#include <mkl.h>
#include <omp.h>
#include <numeric>
#include <algorithm>
#include <math.h>

#define PI 3.1415926535897932384626433832795
#define EPS 1.0e-14

#define BASIC_EXP_ID 0
#define LONG_EXP_ID 1
#define WEIBULL_EXP_ID 2

using namespace std;

struct RunParam
{
	int		task;				// Task id	

	string	path;				// Path to files (if nessesary)

	double	f_in_start;			// Start value of f_in
	double	f_in_shift;			// Shift of f_in
	int		f_in_num;			// Number of slices f_in

	double	b_start;			// Start value of b
	double	b_shift;			// Shift of b
	int		b_num;				// Number of slices b

	int		seed_start;			// Start seed for rng
	int		seed_num;			// Number of seeds
	int		max_num_seeds;		// Maximum number of seeds

	RunParam(
		int _task = 0,

		string _path = "",

		double _f_in_start = 0.5,
		double _f_in_shift = 0.1,
		int _f_in_num = 1,

		double _b_start = 5.0,
		double _b_shift = 1.0,
		int _b_num = 1,

		int _seed_start = 0,
		int _seed_num = 1,
		int _max_num_seeds = 1000000
	)
	{
		task = _task;

		path = _path;

		f_in_start = _f_in_start;
		f_in_shift = _f_in_shift;
		f_in_num = _f_in_num;

		b_start = _b_start;
		b_shift = _b_shift;
		b_num = _b_num;

		seed_start = _seed_start;
		seed_num = _seed_num;
		max_num_seeds = _max_num_seeds;
	}
};

struct ConfigParam
{
	int ns;
	int nsps;

	int ict;

	int nd;

	double thr_Vpost;

	double e_1_alpha_x;

	double e_1_2_f_in;
	double e_1_2_tau;
	double e_1_k_pre;
	
	double e_2_alpha_I;
	double e_2_b;
	double e_2_A;

	double e_3_c;
	double e_3_g_Na;
	double e_3_E_Na;
	double e_3_g_K;
	double e_3_E_K;
	double e_3_g_l;
	double e_3_E_l;
	double e_3_I_th;
	double e_3_theta_x;
	double e_3_k_x;

	double e_4_alpha_a1;
	double e_4_alpha_a2;
	double e_4_alpha_a3;
	double e_4_beta_b1;
	double e_4_beta_b2;
	double e_4_beta_b3;

	double e_5_alpha_a1;
	double e_5_alpha_a2;
	double e_5_beta_b1;
	double e_5_beta_b2;
	double e_5_beta_b3;

	double e_6_alpha_a1;
	double e_6_alpha_a2;
	double e_6_alpha_a3;
	double e_6_beta_b1;
	double e_6_beta_b2;

	int seed;

	ConfigParam(
		double _ns = 100,
		double _nsps = 1000,

		int _ict = 0,

		int _nd = 1,

		double _thr_Vpost = 0.0,

		double _e_1_alpha_x = 0.05,
		double _e_1_k_pre = 1.0,

		double _e_1_2_f_in = 0.5,
		double _e_1_2_tau = 1.0,

		double _e_2_alpha_I = 0.1,
		double _e_2_b = 5.0,
		double _e_2_A = 5.0,

		double _e_3_c = 1.0,
		double _e_3_g_Na = 120.0,
		double _e_3_E_Na = 50.0,
		double _e_3_g_K = 36.0,
		double _e_3_E_K = -77.0,
		double _e_3_g_l = 0.3,
		double _e_3_E_l = -54.4,
		double _e_3_I_th = 8.0,
		double _e_3_theta_x = 0.35,
		double _e_3_k_x = 0.05,

		double _e_4_alpha_a1 = 0.01,
		double _e_4_alpha_a2 = 55.0,
		double _e_4_alpha_a3 = 0.1,
		double _e_4_beta_b1 = 0.125,
		double _e_4_beta_b2 = 65.0,
		double _e_4_beta_b3 = 80.0,

		double _e_5_alpha_a1 = 0.1,
		double _e_5_alpha_a2 = 40.0,
		double _e_5_beta_b1 = 4.0,
		double _e_5_beta_b2 = 65.0,
		double _e_5_beta_b3 = 18.0,

		double _e_6_alpha_a1 = 0.07,
		double _e_6_alpha_a2 = 0.05,
		double _e_6_alpha_a3 = 65.0,
		double _e_6_beta_b1 = 0.1,
		double _e_6_beta_b2 = 35.0,

		int _seed = 0
	)
	{
		ns = _ns;
		nsps = _nsps;

		ict = _ict;

		nd = _nd;

		thr_Vpost = _thr_Vpost;

		e_1_alpha_x = _e_1_alpha_x;
		e_1_k_pre = _e_1_k_pre;

		e_1_2_f_in = _e_1_2_f_in;
		e_1_2_tau = _e_1_2_tau;
		
		e_2_alpha_I = _e_2_alpha_I;
		e_2_b = _e_2_b;
		e_2_A = _e_2_A;

		e_3_c = _e_3_c;
		e_3_g_Na = _e_3_g_Na;
		e_3_E_Na = _e_3_E_Na;
		e_3_g_K = _e_3_g_K;
		e_3_E_K = _e_3_E_K;
		e_3_g_l = _e_3_g_l;
		e_3_E_l = _e_3_E_l;
		e_3_I_th = _e_3_I_th;
		e_3_theta_x = _e_3_theta_x;
		e_3_k_x = _e_3_k_x;

		e_4_alpha_a1 = _e_4_alpha_a1;
		e_4_alpha_a2 = _e_4_alpha_a2;
		e_4_alpha_a3 = _e_4_alpha_a3;
		e_4_beta_b1 = _e_4_beta_b1;
		e_4_beta_b2 = _e_4_beta_b2;
		e_4_beta_b3 = _e_4_beta_b3;

		e_5_alpha_a1 = _e_5_alpha_a1;
		e_5_alpha_a2 = _e_5_alpha_a2;
		e_5_beta_b1 = _e_5_beta_b1;
		e_5_beta_b2 = _e_5_beta_b2;
		e_5_beta_b3 = _e_5_beta_b3;

		e_6_alpha_a1 = _e_6_alpha_a1;
		e_6_alpha_a2 = _e_6_alpha_a2;
		e_6_alpha_a3 = _e_6_alpha_a3;
		e_6_beta_b1 = _e_6_beta_b1;
		e_6_beta_b2 = _e_6_beta_b2;

		seed = _seed;
	}
};


void set_param(RunParam &rp, ConfigParam &cp, string str, string val);

void init_params(RunParam &rp, ConfigParam &cp, char * file_name);

void output_params(RunParam &rp, ConfigParam &cp);
