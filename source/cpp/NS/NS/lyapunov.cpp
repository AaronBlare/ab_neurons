#include "lyapunov.h"

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
