#include "data.h"

void init_main_data(RunParam &rp, ConfigParam &cp, MainData &md)
{
	md.size = 6;

	md.time = 0.0;

	md.step = 1.0 / double(cp.nsps);

	md.time_lim = 0;

	md.A = 0.0;

	vslNewStream(&(md.stream_p), VSL_BRNG_MCG31, 77778888);
	vslLeapfrogStream(md.stream_p, cp.seed, rp.max_num_seeds);

	vslNewStream(&(md.stream_w), VSL_BRNG_MCG31, 77778888);
	vslLeapfrogStream(md.stream_w, cp.seed, rp.max_num_seeds);

	md.data = new double[md.size];
	md.args = new double[md.size];
	md.k1s = new  double[md.size];
	md.k2s = new  double[md.size];
	md.k3s = new  double[md.size];
	md.k4s = new  double[md.size];

	if (rp.task == LONG_EXP_ID)
	{
		md.size_evo = cp.nd + 1;
		md.dump_shift = cp.ns / cp.nd;
	}
	else if (rp.task == BASIC_EXP_ID)
	{
		md.size_evo = cp.ns * cp.nd + 1;
		md.dump_shift = cp.nsps / cp.nd;
	}
	else 
	{
		stringstream msg;
		msg << "Wrong task value: " << rp.task << endl;
		Error(msg.str());
	}
	
	md.curr_dump_id = 0;
	md.data_evo = new double* [md.size];
	md.time_evo = new double[md.size_evo];
	md.I_pre_evo = new double[md.size_evo];

	for (int eq_id = 0; eq_id < md.size; eq_id++)
	{
		md.data[eq_id] = 0.0;
		md.args[eq_id] = 0.0;
		md.k1s[eq_id] = 0.0;
		md.k2s[eq_id] = 0.0;
		md.k3s[eq_id] = 0.0;
		md.k4s[eq_id] = 0.0;

		md.data_evo[eq_id] = new double[md.size_evo];
		for (int dump_id = 0; dump_id < md.size_evo; dump_id++)
		{
			md.data_evo[eq_id][dump_id] = 0.0;

			if (eq_id == 0)
			{
				md.time_evo[dump_id] = 0.0;
				md.I_pre_evo[dump_id] = 0.0;
			}
		}
	}
}

void init_weibull_data(RunParam &rp, ConfigParam &cp, MainData &md)
{
	md.size = 6;

	md.time = 0.0;

	md.step = 1.0 / double(cp.nsps);

	md.time_lim = 0;

	md.A = 0.0;

	vslNewStream(&(md.stream_p), VSL_BRNG_MCG31, 77778888);
	vslLeapfrogStream(md.stream_p, cp.seed, rp.max_num_seeds);

	vslNewStream(&(md.stream_w), VSL_BRNG_MCG31, 77778888);
	vslLeapfrogStream(md.stream_w, cp.seed, rp.max_num_seeds);

	md.size_evo = cp.nd + 1;
	md.dump_shift = cp.ns / cp.nd;
	
	md.curr_dump_id = 0;

	md.A_evo = new double[md.size_evo];
	for (int dump_id = 0; dump_id < md.size_evo; dump_id++)
	{
		md.A_evo[dump_id] = 0.0;
	}
}

void init_lpn_data(ConfigParam &cp, MainData &md)
{
	md.num_lpn = md.size;

	md.data_lpn = new double *[md.num_lpn];
	md.args_lpn = new double *[md.num_lpn];
	md.k1s_lpn = new double *[md.num_lpn];
	md.k2s_lpn = new double *[md.num_lpn];
	md.k3s_lpn = new double *[md.num_lpn];
	md.k4s_lpn = new double *[md.num_lpn];

	md.norms_lpn = new double[md.num_lpn];
	md.exps_lpn = new double[md.num_lpn];
	md.rvm_lpn = new double[md.num_lpn];

	for (int lpn_id = 0; lpn_id < md.num_lpn; lpn_id++)
	{
		md.data_lpn[lpn_id] = new double[md.size];
		md.args_lpn[lpn_id] = new double[md.size];
		md.k1s_lpn[lpn_id] = new double[md.size];
		md.k2s_lpn[lpn_id] = new double[md.size];
		md.k3s_lpn[lpn_id] = new double[md.size];
		md.k4s_lpn[lpn_id] = new double[md.size];

		for (int eq_id = 0; eq_id < md.size; eq_id++)
		{
			md.data_lpn[lpn_id][eq_id] = 0.0;
			md.args_lpn[lpn_id][eq_id] = 0.0;
			md.k1s_lpn[lpn_id][eq_id] = 0.0;
			md.k2s_lpn[lpn_id][eq_id] = 0.0;
			md.k3s_lpn[lpn_id][eq_id] = 0.0;
			md.k4s_lpn[lpn_id][eq_id] = 0.0;
		}

		md.norms_lpn[lpn_id] = 0.0;
		md.exps_lpn[lpn_id] = 0.0;
		md.rvm_lpn[lpn_id] = 0.0;
	}
}

void delete_main_data(MainData &md)
{
	delete_data(md.data);
	delete_data(md.args);
	delete_data(md.k1s);
	delete_data(md.k2s);
	delete_data(md.k3s);
	delete_data(md.k4s);

	for (int eq_id = 0; eq_id < md.size; eq_id++)
	{
		delete[] md.data_evo[eq_id];
	}
	delete[] md.data_evo;
	delete[] md.time_evo;
	delete[] md.I_pre_evo;
}

void delete_weibull_data(MainData &md)
{
	delete[] md.A_evo;
}

void delete_lpn_data(MainData &md)
{
	for (int lpn_id = 0; lpn_id < md.num_lpn; lpn_id++)
	{
		delete[] md.data_lpn[lpn_id];
		delete[] md.args_lpn[lpn_id];
		delete[] md.k1s_lpn[lpn_id];
		delete[] md.k2s_lpn[lpn_id];
		delete[] md.k3s_lpn[lpn_id];
		delete[] md.k4s_lpn[lpn_id];
	}

	delete[] md.data_lpn;
	delete[] md.args_lpn;
	delete[] md.k1s_lpn;
	delete[] md.k2s_lpn;
	delete[] md.k3s_lpn;
	delete[] md.k4s_lpn;

	delete[] md.norms_lpn;
	delete[] md.exps_lpn;
	delete[] md.rvm_lpn;
}

void init_cond(RunParam &rp, ConfigParam &cp, MainData &md)
{
	md.data[0] = 0.0;
	md.data[1] = 0.0;
	md.data[2] = 0.0;
	md.data[3] = 0.0;
	md.data[4] = 0.0;
	md.data[5] = 0.0;

	md.time_evo[md.curr_dump_id] = md.time;
	md.I_pre_evo[md.curr_dump_id] = 0;

	for (int eq_id = 0; eq_id < md.size; eq_id++)
	{
		md.data_evo[eq_id][md.curr_dump_id] = md.data[eq_id];
	}

	md.curr_dump_id++;
}

void init_cond_lpn(ConfigParam &cp, MainData &md)
{
	for (int lpn_id = 0; lpn_id < md.num_lpn; lpn_id++)
	{
		md.data_lpn[lpn_id][lpn_id] = 1.0;
	}
}

void calc_norm_lpn(MainData &md, int lpn_id)
{
	double sum = 0.0;

	for (int st_id = 0; st_id < md.size; st_id++)
	{
		sum += (md.data_lpn[lpn_id][st_id] * md.data_lpn[lpn_id][st_id]);
	}

	md.norms_lpn[lpn_id] = sqrt(sum);
}

void normalization_lpn(MainData &md, int lpn_id)
{
	for (int eq_id = 0; eq_id < md.size; eq_id++)
	{
		md.data_lpn[lpn_id][eq_id] = md.data_lpn[lpn_id][eq_id] / md.norms_lpn[lpn_id];
	}
}

void scalar_mult_lpn(MainData &md, double * mults, int lpn_id, int lpn_id_tmp)
{
	for (int eq_id = 0; eq_id < md.size; eq_id++)
	{
		mults[lpn_id_tmp] += md.data_lpn[lpn_id][eq_id] * md.data_lpn[lpn_id_tmp][eq_id];
	}
}

void sub_lpn(MainData &md, double* mults, int lpn_id, int lpn_id_tmp)
{
	for (int eq_id = 0; eq_id < md.size; eq_id++)
	{
		md.data_lpn[lpn_id][eq_id] -= mults[lpn_id_tmp] * md.data_lpn[lpn_id_tmp][eq_id];
	}
}

void gsorth_lpn(MainData &md)
{
	/* Compute first norm */
	int lpn_id = 0;
	calc_norm_lpn(md, lpn_id);
	/* Renorm - find first vector in new basis */
	normalization_lpn(md, lpn_id);

	/* Find  others basis vectors */
	for (int lpn_id = 1; lpn_id < md.num_lpn; lpn_id++)
	{
		/* Firstly find all nessesary scalar mults */
		double *mults = new double[md.num_lpn];

		for (int lpn_id_tmp = 0; lpn_id_tmp < lpn_id; lpn_id_tmp++)
		{
			mults[lpn_id_tmp] = 0.0;
			scalar_mult_lpn(md, mults, lpn_id, lpn_id_tmp);
		}

		/* Compute unnormed basis vector using scalar mults*/
		for (int lpn_id_tmp = 0; lpn_id_tmp < lpn_id; lpn_id_tmp++)
		{
			sub_lpn(md, mults, lpn_id, lpn_id_tmp);
		}

		delete[] mults;

		/* Find norm of new basis vector */
		calc_norm_lpn(md, lpn_id);

		/* Renorm new vector */
		normalization_lpn(md, lpn_id);
	}

	/* Calculate Lyapunov exps */

	for (int lpn_id = 0; lpn_id < md.num_lpn; lpn_id++)
	{
		md.rvm_lpn[lpn_id] += log(md.norms_lpn[lpn_id]);
		md.exps_lpn[lpn_id] = md.rvm_lpn[lpn_id] / md.time;
	}
}

