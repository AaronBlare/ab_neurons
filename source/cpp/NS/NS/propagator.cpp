#include "propagator.h"

void SimplePropagationBehavior::propagate(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb) const
{
	viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->stream_p, 1, &(md->time_lim), cp->e_1_2_f_in);

	double impulse = 0.0;

	int curr_sec_id = 0;
	int lim_sec_id = 0;
	int curr_sec_window = 0;

	if (md->time_lim <= cp->ns)
	{
		for (int sec_id = 0; sec_id < md->time_lim; sec_id++)
		{
			int_second(rp, cp, md, rpb, sec_id, impulse);
		}

		curr_sec_id = md->time_lim;

		while (curr_sec_id < cp->ns)
		{
			curr_sec_window = 1;

			vdRngWeibull(VSL_RNG_METHOD_WEIBULL_ICDF, md->stream_w, 1, &(md->A), 2.0, 0.0, cp->e_2_b);

			viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->stream_p, 1, &(md->time_lim), cp->e_1_2_f_in);

			while (md->time_lim <= 1)
			{
				curr_sec_window += md->time_lim;
				viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->stream_p, 1, &(md->time_lim), cp->e_1_2_f_in);
			}

			lim_sec_id = curr_sec_id + (curr_sec_window - 1) + md->time_lim;

			impulse = 1.0;
			for (int sec_id = curr_sec_id; sec_id < min(curr_sec_id + curr_sec_window, cp->ns); sec_id++)
			{
				int_second(rp, cp, md, rpb, sec_id, impulse);
			}

			curr_sec_id += curr_sec_window;

			impulse = 0.0;
			for (int sec_id = curr_sec_id; sec_id < min(lim_sec_id, cp->ns); sec_id++)
			{
				int_second(rp, cp, md, rpb, sec_id, impulse);
			}

			curr_sec_id += lim_sec_id - curr_sec_id;
		}
	}
	else
	{
		for (int sec_id = 0; sec_id < cp->ns; sec_id++)
		{
			int_second(rp, cp, md, rpb, sec_id, impulse);
		}
	}
}

void FullPropagationBehavior::propagate(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb) const
{
	viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->stream_p, 1, &(md->time_lim), cp->e_1_2_f_in);

	double impulse = 0.0;

	int curr_sec_id = 0;
	int lim_sec_id = 0;
	int curr_sec_window = 0;

	if (md->time_lim <= cp->ns)
	{
		for (int sec_id = 0; sec_id < md->time_lim; sec_id++)
		{
			int_second(rp, cp, md, rpb, sec_id, impulse);
		}

		curr_sec_id = md->time_lim;

		while (curr_sec_id < cp->ns)
		{
			curr_sec_window = 1;

			double b = cp->e_2_b * (1.0 + cp->e_y2_gamma * md->data[7]);
			vdRngWeibull(VSL_RNG_METHOD_WEIBULL_ICDF, md->stream_w, 1, &(md->A), 2.0, 0.0, cp->e_2_b);

			viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->stream_p, 1, &(md->time_lim), cp->e_1_2_f_in);

			while (md->time_lim <= 1)
			{
				curr_sec_window += md->time_lim;
				viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->stream_p, 1, &(md->time_lim), cp->e_1_2_f_in);
			}

			lim_sec_id = curr_sec_id + (curr_sec_window - 1) + md->time_lim;

			impulse = 1.0;
			for (int sec_id = curr_sec_id; sec_id < min(curr_sec_id + curr_sec_window, cp->ns); sec_id++)
			{
				int_second(rp, cp, md, rpb, sec_id, impulse);
			}

			curr_sec_id += curr_sec_window;

			impulse = 0.0;
			for (int sec_id = curr_sec_id; sec_id < min(lim_sec_id, cp->ns); sec_id++)
			{
				int_second(rp, cp, md, rpb, sec_id, impulse);
			}

			curr_sec_id += lim_sec_id - curr_sec_id;
		}
	}
	else
	{
		for (int sec_id = 0; sec_id < cp->ns; sec_id++)
		{
			int_second(rp, cp, md, rpb, sec_id, impulse);
		}
	}
}

void upd_arg(int size, double * x_arg, double * x, double * ks, double coeff)
{
	for (int eq_id = 0; eq_id < size; eq_id++)
	{
		x_arg[eq_id] = x[eq_id] + coeff * ks[eq_id];
	}
}

void rk_final(int size, double * x, double * k1s, double * k2s, double * k3s, double * k4s, double step)
{
	for (int eq_id = 0; eq_id < size; eq_id++)
	{
		x[eq_id] += (k1s[eq_id] + 2.0 * k2s[eq_id] + 2.0 * k3s[eq_id] + k4s[eq_id]) * step / 6.0;
	}
}

void rk_step(ConfigParam * cp, MainData * md, RightPartBehavior * rpb, double impulse)
{
	rpb->right_part(cp, md, md->k1s, md->data, md->time, impulse);
	upd_arg(md->size, md->args, md->data, md->k1s, md->step * 0.5);

	md->time += md->step * 0.5;

	rpb->right_part(cp, md, md->k2s, md->args, md->time, impulse);
	upd_arg(md->size, md->args, md->data, md->k2s, md->step * 0.5);

	rpb->right_part(cp, md, md->k3s, md->args, md->time, impulse);
	upd_arg(md->size, md->args, md->data, md->k3s, md->step * 1.0);

	md->time += md->step * 0.5;

	rpb->right_part(cp, md, md->k4s, md->args, md->time, impulse);

	rk_final(md->size, md->data, md->k1s, md->k2s, md->k3s, md->k4s, md->step);
}

void int_second(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb, int sec_id, double impulse)
{
	for (int step_id = 0; step_id < cp->nsps; step_id++)
	{
		md->time = double(sec_id) + double(step_id) * md->step;
		rk_step(cp, md, rpb, impulse);
		md->time = double(sec_id) + double(step_id + 1) * md->step;

		double curr_Vpost = md->data[2];

		if (curr_Vpost > cp->thr_Vpost)
		{
			if (md->curr_Vpost_status == 0)
			{
				md->curr_Vpost_status = 1;
				md->num_thr_cross_Vpost++;
			}
		}
		else
		{
			if (md->curr_Vpost_status == 1)
			{
				md->curr_Vpost_status = 0;
			}
		}

		if (rp->task == BASIC_EXP_ID)
		{
			if (step_id % md->dump_shift == 0)
			{
				md->time_evo[md->curr_dump_id] = md->time;
				md->I_pre_evo[md->curr_dump_id] = impulse;

				for (int eq_id = 0; eq_id < md->size; eq_id++)
				{
					md->data_evo[eq_id][md->curr_dump_id] = md->data[eq_id];
				}

				md->curr_dump_id++;
			}
		}
	}

	if (rp->task == LONG_EXP_ID)
	{
		if (sec_id % md->dump_shift == 0)
		{
			md->time_evo[md->curr_dump_id] = md->time;
			md->I_pre_evo[md->curr_dump_id] = impulse;

			for (int eq_id = 0; eq_id < md->size; eq_id++)
			{
				md->data_evo[eq_id][md->curr_dump_id] = md->data[eq_id];
			}

			md->curr_dump_id++;
		}

		if (sec_id % (cp->ns / 100) == 0)
		{
			cout << "ms: " << (sec_id + 1) << endl;
		}

	}
}


