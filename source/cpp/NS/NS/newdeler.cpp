#include "newdeler.h"

void SimpleNewDelBehaviour::init_data(RunParam * rp, ConfigParam * cp, MainData * md) const
{
	init_all_data(rp, cp, md, 6);
}

void SimpleNewDelBehaviour::free_data(RunParam * rp, ConfigParam * cp, MainData * md) const
{
	free_all_data(md);
}

void FullNewDelBehaviour::init_data(RunParam * rp, ConfigParam * cp, MainData * md) const
{
	init_all_data(rp, cp, md, 8);
}

void FullNewDelBehaviour::free_data(RunParam * rp, ConfigParam * cp, MainData * md) const
{
	free_all_data(md);
}

void init_all_data(RunParam * rp, ConfigParam * cp, MainData * md, int size)
{
	init_model_data(rp, cp, md, size);
	init_random_data(rp, cp, md);
	init_evo_data(rp, cp, md);
	init_propagation_data(rp, cp, md);
	init_start(rp, cp, md);
}

void init_model_data(RunParam * rp, ConfigParam * cp, MainData * md, int size)
{
	md->size = size;

	md->time = 0.0;

	md->step = 1.0 / double(cp->nsps);

	md->time_lim = 0;

	md->A = 0.0;

	md->curr_Vpost_status = 0;
	md->num_thr_cross_Vpost = 0;

	md->f_out = 0.0;
}

void init_random_data(RunParam * rp, ConfigParam * cp, MainData * md)
{
	vslNewStream(&(md->stream_p), VSL_BRNG_MCG31, 77778888);
	vslLeapfrogStream(md->stream_p, cp->seed, rp->max_num_seeds);

	vslNewStream(&(md->stream_w), VSL_BRNG_MCG31, 77778888);
	vslLeapfrogStream(md->stream_w, cp->seed, rp->max_num_seeds);
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
	md->data_evo = new double*[md->size];
	md->time_evo = new double[md->size_evo];
	md->I_pre_evo = new double[md->size_evo];

	for (int eq_id = 0; eq_id < md->size; eq_id++)
	{
		md->data_evo[eq_id] = new double[md->size_evo];
		for (int dump_id = 0; dump_id < md->size_evo; dump_id++)
		{
			md->data_evo[eq_id][dump_id] = 0.0;

			if (eq_id == 0)
			{
				md->time_evo[dump_id] = 0.0;
				md->I_pre_evo[dump_id] = 0.0;
			}
		}
	}
}

void init_propagation_data(RunParam * rp, ConfigParam * cp, MainData * md)
{
	md->data = new double[md->size];
	md->args = new double[md->size];
	md->k1s = new  double[md->size];
	md->k2s = new  double[md->size];
	md->k3s = new  double[md->size];
	md->k4s = new  double[md->size];

	for (int eq_id = 0; eq_id < md->size; eq_id++)
	{
		md->data[eq_id] = 0.0;
		md->args[eq_id] = 0.0;
		md->k1s[eq_id] = 0.0;
		md->k2s[eq_id] = 0.0;
		md->k3s[eq_id] = 0.0;
		md->k4s[eq_id] = 0.0;
	}
}

void init_start(RunParam * rp, ConfigParam * cp, MainData * md)
{
	md->time_evo[md->curr_dump_id] = md->time;
	md->I_pre_evo[md->curr_dump_id] = 0;

	for (int eq_id = 0; eq_id < md->size; eq_id++)
	{
		md->data[eq_id] = 0.0;
		md->data_evo[eq_id][md->curr_dump_id] = md->data[eq_id];
	}

	md->curr_dump_id++;
}

void free_all_data(MainData * md)
{
	del(md->data);
	del(md->args);
	del(md->k1s);
	del(md->k2s);
	del(md->k3s);
	del(md->k4s);

	for (int eq_id = 0; eq_id < md->size; eq_id++)
	{
		delete[] md->data_evo[eq_id];
	}
	delete[] md->data_evo;

	delete[] md->time_evo;
	delete[] md->I_pre_evo;
}
