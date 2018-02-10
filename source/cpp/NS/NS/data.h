#pragma once
#include "config.h"
#include "utils.h"

struct MainData
{
	int num_neurons;		// Number of neurons
	int size_neu;			// Data size for neurons
	int size_env;			// Data size for enviroment

	double time;			// Current integration time

	double step;			// Integration step

	int * time_lim;			// Current time limit for neurons
	double * A;				// Current A for neurons

	VSLStreamStatePtr * streams_p;	// Streams for Poisson
	VSLStreamStatePtr * streams_w;	// Stream for Weibull

	double ** data_neu;			// Integration data for neurons
	double ** args_neu;			// Integration routines data for neurons
	double ** k1s_neu;			// Integration routines data for neurons
	double ** k2s_neu;			// Integration routines data for neurons
	double ** k3s_neu;			// Integration routines data for neurons
	double ** k4s_neu;			// Integration routines data for neurons

	double * data_env;			// Integration data for enviroment
	double * args_env;			// Integration routines data for enviroment
	double * k1s_env;			// Integration routines data for enviroment
	double * k2s_env;			// Integration routines data for enviroment
	double * k3s_env;			// Integration routines data for enviroment
	double * k4s_env;			// Integration routines data for enviroment

	int size_evo;				// Size of evo data
	int curr_dump_id;			// Current dump id
	double *** data_neu_evo;	// Data evolution for neurons
	double ** data_env_evo;		// Data evolution for enviroment
	double * time_evo;			// Time evolution
	double * A_evo;				// A evolution

	int dump_shift;			// Dump shift

	int * curr_Vpost_status;	// Current status of Vpost
	int * num_thr_cross_Vpost;	// Total number of crossings
	double * f_out;				// f_out
};

