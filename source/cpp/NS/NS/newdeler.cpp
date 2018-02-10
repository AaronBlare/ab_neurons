#include "newdeler.h"

void SimpleNewDelBehaviour::init_data(RunParam * rp, ConfigParam * cp, MainData * md) const
{
	init_all_data(rp, cp, md, 0);
}

void SimpleNewDelBehaviour::free_data(RunParam * rp, ConfigParam * cp, MainData * md) const
{
	free_all_data(rp, cp, md);
}

void FullNewDelBehaviour::init_data(RunParam * rp, ConfigParam * cp, MainData * md) const
{
	init_all_data(rp, cp, md, 1);
}

void FullNewDelBehaviour::free_data(RunParam * rp, ConfigParam * cp, MainData * md) const
{
	free_all_data(rp, cp, md);
}

void init_all_data(RunParam * rp, ConfigParam * cp, MainData * md, int is_env)
{
	init_model_data(rp, cp, md, is_env);
	init_random_data(rp, cp, md);
	init_evo_data(rp, cp, md);
	init_propagation_data(rp, cp, md);
	init_start(rp, cp, md);
}

void init_model_data(RunParam * rp, ConfigParam * cp, MainData * md, int is_env)
{
	if (is_env == 0)
	{
		md->size_env = 0;
	}
	else
	{
		md->size_env = 2;
	}
	
	md->size_neu = 6;

	md->time = 0.0;

	md->step = 1.0 / double(cp->nsps);

	md->time_lim = new int[cp->nn];
	md->A = new double[cp->nn];
	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		md->time_lim[n_id] = 0;
		md->A[n_id] = 0.0;
	}

	md->curr_Vpost_status = new int[cp->nn];
	md->num_thr_cross_Vpost = new int[cp->nn];
	md->f_out = new double[cp->nn];
	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		md->curr_Vpost_status[n_id] = 0;
		md->num_thr_cross_Vpost[n_id] = 0;
		md->f_out[n_id] = 0.0;
	}
}

void init_random_data(RunParam * rp, ConfigParam * cp, MainData * md)
{
	md->streams_p = new VSLStreamStatePtr[cp->nn];
	md->streams_w = new VSLStreamStatePtr[cp->nn];
	vslNewStream(&(md->streams_p)[0], VSL_BRNG_MCG31, 77778888);
	vslNewStream(&(md->streams_w)[0], VSL_BRNG_MCG31, 77778888);
	for (int n_id = 1; n_id < cp->nn; n_id++)
	{
		vslCopyStream(&(md->streams_p)[n_id], (md->streams_p)[0]);
		vslCopyStream(&(md->streams_w)[n_id], (md->streams_w)[0]);
	}

	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		vslLeapfrogStream((md->streams_p)[n_id], cp->seed + n_id, rp->max_num_seeds);
		vslLeapfrogStream((md->streams_w)[n_id], cp->seed + n_id, rp->max_num_seeds);
	}
}

void init_evo_data(RunParam * rp, ConfigParam * cp, MainData * md)
{
	if (rp->task == LONG_EXP_ID)
	{
		md->size_evo = cp->nd + 1;
		md->dump_shift = cp->ns / cp->nd;
	}
	else if (rp->task == BASIC_EXP_ID)
	{
		md->size_evo = cp->ns * cp->nd + 1;
		md->dump_shift = cp->nsps / cp->nd;
	}
	else
	{
		stringstream msg;
		msg << "Wrong task value: " << rp->task << endl;
		Error(msg.str());
	}

	md->curr_dump_id = 0;

	md->data_neu_evo = new double**[cp->nn];
	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		md->data_neu_evo[n_id] = new double*[md->size_neu];
		for (int eq_id = 0; eq_id < md->size_neu; eq_id++)
		{
			md->data_neu_evo[n_id][eq_id] = new double[md->size_evo];
			for (int dump_id = 0; dump_id < md->size_evo; dump_id++)
			{
				md->data_neu_evo[n_id][eq_id][dump_id] = 0.0;
			}
		}
	}

	if (md->size_env > 0)
	{
		md->data_env_evo = new double*[md->size_env];
		for (int eq_id = 0; eq_id < md->size_env; eq_id++)
		{
			md->data_env_evo[eq_id] = new double[md->size_evo];
			for (int dump_id = 0; dump_id < md->size_evo; dump_id++)
			{
				md->data_env_evo[eq_id][dump_id] = 0.0;
			}
		}
	}
	
	md->time_evo = new double[md->size_evo];
	for (int dump_id = 0; dump_id < md->size_evo; dump_id++)
	{
		md->time_evo[dump_id] = 0.0;
	}
}

void init_propagation_data(RunParam * rp, ConfigParam * cp, MainData * md)
{
	md->data_neu = new double*[cp->nn];
	md->args_neu = new double*[cp->nn];
	md->k1s_neu = new  double*[cp->nn];
	md->k2s_neu = new  double*[cp->nn];
	md->k3s_neu = new  double*[cp->nn];
	md->k4s_neu = new  double*[cp->nn];

	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		md->data_neu[n_id] = new double[md->size_neu];
		md->args_neu[n_id] = new double[md->size_neu];
		md->k1s_neu[n_id] = new  double[md->size_neu];
		md->k2s_neu[n_id] = new  double[md->size_neu];
		md->k3s_neu[n_id] = new  double[md->size_neu];
		md->k4s_neu[n_id] = new  double[md->size_neu];

		for (int eq_id = 0; eq_id < md->size_neu; eq_id++)
		{
			md->data_neu[n_id][eq_id] = 0.0;
			md->args_neu[n_id][eq_id] = 0.0;
			md->k1s_neu[n_id][eq_id] = 0.0;
			md->k2s_neu[n_id][eq_id] = 0.0;
			md->k3s_neu[n_id][eq_id] = 0.0;
			md->k4s_neu[n_id][eq_id] = 0.0;
		}
	}

	if (md->size_env > 0)
	{
		md->data_env = new double[md->size_env];
		md->args_env = new double[md->size_env];
		md->k1s_env = new  double[md->size_env];
		md->k2s_env = new  double[md->size_env];
		md->k3s_env = new  double[md->size_env];
		md->k4s_env = new  double[md->size_env];

		for (int eq_id = 0; eq_id < md->size_env; eq_id++)
		{
			md->data_env[eq_id] = 0.0;
			md->args_env[eq_id] = 0.0;
			md->k1s_env[eq_id] = 0.0;
			md->k2s_env[eq_id] = 0.0;
			md->k3s_env[eq_id] = 0.0;
			md->k4s_env[eq_id] = 0.0;
		}
	}
}

void init_start(RunParam * rp, ConfigParam * cp, MainData * md)
{
	md->time_evo[md->curr_dump_id] = md->time;

	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		for (int eq_id = 0; eq_id < md->size_neu; eq_id++)
		{
			md->data_neu[n_id][eq_id] = 0.0;
			md->data_neu_evo[n_id][eq_id][md->curr_dump_id] = md->data_neu[n_id][eq_id];
		}
	}

	if (md->size_env > 0)
	{
		for (int eq_id = 0; eq_id < md->size_env; eq_id++)
		{
			md->data_env[eq_id] = 0.0;
			md->data_env_evo[eq_id][md->curr_dump_id] = md->data_env[eq_id];
		}
	}

	md->curr_dump_id++;
}

void free_all_data(RunParam * rp, ConfigParam * cp, MainData * md)
{
	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		delete[] md->data_neu[n_id];
		delete[] md->args_neu[n_id];
		delete[] md->k1s_neu[n_id];
		delete[] md->k2s_neu[n_id];
		delete[] md->k3s_neu[n_id];
		delete[] md->k4s_neu[n_id];
	}
	delete[] md->data_neu;
	delete[] md->args_neu;
	delete[] md->k1s_neu;
	delete[] md->k2s_neu;
	delete[] md->k3s_neu;
	delete[] md->k4s_neu;

	if (md->size_env > 0)
	{
		delete[] md->data_env;
		delete[] md->args_env;
		delete[] md->k1s_env;
		delete[] md->k2s_env;
		delete[] md->k3s_env;
		delete[] md->k4s_env;
	}

	delete[] md->time_evo;

	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		for (int eq_id = 0; eq_id < md->size_neu; eq_id++)
		{
			delete[] md->data_neu_evo[n_id][eq_id];
		}
		delete[] md->data_neu_evo[n_id];
	}
	delete[] md->data_neu_evo;

	if (md->size_env > 0)
	{
		for (int eq_id = 0; eq_id < md->size_env; eq_id++)
		{
			delete[] md->data_env_evo[eq_id];
		}
		delete[] md->data_env_evo;
	}

	free_model_data(md);
}

void free_model_data(MainData * md)
{
	delete[] md->time_lim;
	delete[] md->A;

	delete[] md->curr_Vpost_status;
	delete[] md->num_thr_cross_Vpost;
	delete[] md->f_out;

	delete[] md->streams_p;
	delete[] md->streams_w;
}
