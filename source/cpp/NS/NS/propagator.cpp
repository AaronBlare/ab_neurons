#include "propagator.h"

void SimplePropagationBehavior::propagate(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb) const
{
	int * last_impulse = new int[cp->nn];
	double * impulses = new double[cp->nn];
	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->streams_p[n_id], 1, &(md->time_lim[n_id]), cp->e_1_2_f_in);
		last_impulse[n_id] = -1;
		impulses[n_id] = 0.0;
	}

	for (int sec_id = 0; sec_id < cp->ns; sec_id++)
	{
		for (int n_id = 0; n_id < cp->nn; n_id++)
		{
			if (sec_id == md->time_lim[n_id])
			{
				int time_lim = 0;

				vdRngWeibull(VSL_RNG_METHOD_WEIBULL_ICDF, md->streams_w[n_id], 1, &(md->A[n_id]), 2.0, 0.0, cp->e_2_b);

				viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->streams_p[n_id], 1, &time_lim, cp->e_1_2_f_in);
				md->time_lim[n_id] += time_lim;

				while (time_lim <= 1)
				{
					viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->streams_p[n_id], 1, &time_lim, cp->e_1_2_f_in);
					md->time_lim[n_id] += time_lim;
				}

				last_impulse[n_id] = md->time_lim[n_id] - time_lim + 1;
			}

			if (sec_id < last_impulse[n_id])
			{
				impulses[n_id] = 1.0;
			}
			else
			{
				impulses[n_id] = 0.0;
			}
		}

		int_second(rp, cp, md, rpb, sec_id, impulses);
	}

	delete[] last_impulse;
}

void FullPropagationBehavior::propagate(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb) const
{
	int * last_impulse = new int[cp->nn];
	double * impulses = new double[cp->nn];
	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->streams_p[n_id], 1, &(md->time_lim[n_id]), cp->e_1_2_f_in);
		last_impulse[n_id] = -1;
		impulses[n_id] = 0.0;
	}

	for (int sec_id = 0; sec_id < cp->ns; sec_id++)
	{
		for (int n_id = 0; n_id < cp->nn; n_id++)
		{
			if (sec_id == md->time_lim[n_id])
			{
				int time_lim = 0;

				double b = cp->e_2_b * (1.0 + cp->e_y2_gamma * md->data_env[1]);
				vdRngWeibull(VSL_RNG_METHOD_WEIBULL_ICDF, md->streams_w[n_id], 1, &(md->A[n_id]), 2.0, 0.0, b);

				viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->streams_p[n_id], 1, &time_lim, cp->e_1_2_f_in);
				md->time_lim[n_id] += time_lim;

				while (time_lim <= 1)
				{
					viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->streams_p[n_id], 1, &time_lim, cp->e_1_2_f_in);
					md->time_lim[n_id] += time_lim;
				}

				last_impulse[n_id] = md->time_lim[n_id] - time_lim + 1;
			}

			if (sec_id < last_impulse[n_id])
			{
				impulses[n_id] = 1.0;
			}
			else
			{
				impulses[n_id] = 0.0;
			}
		}

		int_second(rp, cp, md, rpb, sec_id, impulses);
	}

	delete[] last_impulse;
}

void rk_step(ConfigParam * cp, MainData * md, RightPartBehavior * rpb, double * impulses)
{
	rpb->set_init_args(cp, md);

	rpb->right_part(cp, md, 1, impulses);
	rpb->update_arg(cp, md, 1, md->step * 0.5);

	md->time += md->step * 0.5;

	rpb->right_part(cp, md, 2, impulses);
	rpb->update_arg(cp, md, 2, md->step * 0.5);

	rpb->right_part(cp, md, 3, impulses);
	rpb->update_arg(cp, md, 3, md->step * 1.0);

	md->time += md->step * 0.5;

	rpb->right_part(cp, md, 4, impulses);

	rpb->rk_final(cp, md, md->step);
}

void int_second(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb, int sec_id, double * impulses)
{
	for (int step_id = 0; step_id < cp->nsps; step_id++)
	{
		md->time = double(sec_id) + double(step_id) * md->step;
		rk_step(cp, md, rpb, impulses);
		md->time = double(sec_id) + double(step_id + 1) * md->step;

		for (int n_id = 0; n_id < cp->nn; n_id++)
		{
			double curr_Vpost = md->data_neu[n_id][2];

			if (curr_Vpost > cp->thr_Vpost)
			{
				if (md->curr_Vpost_status[n_id] == 0)
				{
					md->curr_Vpost_status[n_id] = 1;
					md->num_thr_cross_Vpost[n_id]++;
				}
			}
			else
			{
				if (md->curr_Vpost_status[n_id] == 1)
				{
					md->curr_Vpost_status[n_id] = 0;
				}
			}
		}

		if (rp->task == BASIC_EXP_ID)
		{
			if (step_id % md->dump_shift == 0)
			{
				md->time_evo[md->curr_dump_id] = md->time;

				for (int n_id = 0; n_id < cp->nn; n_id++)
				{
					for (int eq_id = 0; eq_id < md->size_neu; eq_id++)
					{
						md->data_neu_evo[n_id][eq_id][md->curr_dump_id] = md->data_neu[n_id][eq_id];
					}
				}

				if (md->size_env > 0)
				{
					for (int eq_id = 0; eq_id < md->size_env; eq_id++)
					{
						md->data_env_evo[eq_id][md->curr_dump_id] = md->data_env[eq_id];
					}
				}

				md->curr_dump_id++;
			}
		}

	}

	if (rp->task == LONG_EXP_ID)
	{
		if ((sec_id + 1) % md->dump_shift == 0)
		{
			md->time_evo[md->curr_dump_id] = md->time;

			for (int n_id = 0; n_id < cp->nn; n_id++)
			{
				for (int eq_id = 0; eq_id < md->size_neu; eq_id++)
				{
					md->data_neu_evo[n_id][eq_id][md->curr_dump_id] = md->data_neu[n_id][eq_id];
				}
			}

			if (md->size_env > 0)
			{
				for (int eq_id = 0; eq_id < md->size_env; eq_id++)
				{
					md->data_env_evo[eq_id][md->curr_dump_id] = md->data_env[eq_id];
				}
			}

			md->curr_dump_id++;
		}

		if ((sec_id + 1) % (cp->ns / 100) == 0)
		{
			cout << "ms: " << (sec_id + 1) << endl;
		}
	}
}


