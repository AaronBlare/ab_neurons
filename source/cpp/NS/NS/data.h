#pragma once
#include "config.h"
#include "utils.h"

struct MainData
{
	int size;				// Data size

	double time;			// Current integration time

	double step;			// Integration step

	int time_lim;			// Current time limit

	double A;				// Current A

	VSLStreamStatePtr stream_p;		// Stream for Poisson
	VSLStreamStatePtr stream_w;		// Stream for Weibull

	double * data;			// Integration data
	double * args;			// Integration routines data
	double * k1s;			// Integration routines data
	double * k2s;			// Integration routines data
	double * k3s;			// Integration routines data
	double * k4s;			// Integration routines data

	int size_evo;			// Size of evo data
	int curr_dump_id;		// Current dump id
	double ** data_evo;		// Data evolution
	double * time_evo;		// Time evolution
	double * I_pre_evo;		// I_pre evolution
	double * A_evo;			// A evolution

	int dump_shift;			// Dump shift

	int curr_Vpost_status;		// Current status of Vpost
	int num_thr_cross_Vpost;	// Total number of crossings
	double f_out;				// f_out

	int num_lpn;			// Number of Lyapunov exponents

	double ** data_lpn;		// Data for Lyapunov exps
	double ** args_lpn;		// Integration Lyapunov routines data
	double ** k1s_lpn;		// Integration Lyapunov routines data
	double ** k2s_lpn;		// Integration Lyapunov routines data
	double ** k3s_lpn;		// Integration Lyapunov routines data
	double ** k4s_lpn;		// Integration Lyapunov routines data
	double * norms_lpn;		// Norms for Lyapunov vectors
	double * exps_lpn;		// Lyapunov exponents
	double * rvm_lpn;		// Aux data for Lyapunov exponents
};


void init_main_data(RunParam &rp, ConfigParam &cp, MainData &md);

void init_weibull_data(RunParam &rp, ConfigParam &cp, MainData &md);

void init_lpn_data(ConfigParam &cp, MainData &md);

void delete_main_data(MainData &dt);

void delete_weibull_data(MainData &dt);

void delete_lpn_data(MainData &md);

void init_cond(RunParam &rp, ConfigParam &cp, MainData &md);

void init_cond_lpn(ConfigParam &cp, MainData &md);

void calc_norm_lpn(MainData &md, int lpn_id);

void normalization_lpn(MainData &md, int lpn_id);

void scalar_mult_lpn(MainData &md, double * mults, int lpn_id, int lpn_id_tmp);

void sub_lpn(MainData &md, double* mults, int lpn_id, int lpn_id_tmp);

void gsorth_lpn(MainData &md);

