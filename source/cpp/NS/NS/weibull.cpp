#include "weibull.h"

void init_weibull_data(RunParam * rp, ConfigParam * cp, MainData * md)
{
	md->size = 6;

	md->time = 0.0;

	md->step = 1.0 / double(cp->nsps);

	md->time_lim = 0;

	md->A = 0.0;

	vslNewStream(&(md->stream_p), VSL_BRNG_MCG31, 77778888);
	vslLeapfrogStream(md->stream_p, cp->seed, rp->max_num_seeds);

	vslNewStream(&(md->stream_w), VSL_BRNG_MCG31, 77778888);
	vslLeapfrogStream(md->stream_w, cp->seed, rp->max_num_seeds);

	md->size_evo = cp->nd + 1;
	md->dump_shift = cp->ns / cp->nd;

	md->curr_dump_id = 0;

	md->A_evo = new double[md->size_evo];
	for (int dump_id = 0; dump_id < md->size_evo; dump_id++)
	{
		md->A_evo[dump_id] = 0.0;
	}
}

void weibull_dist(RunParam * rp, ConfigParam * cp, MainData * md)
{
	for (int dump_id = 0; dump_id < md->size_evo; dump_id++)
	{
		vdRngWeibull(VSL_RNG_METHOD_WEIBULL_ICDF, md->stream_w, 1, &(md->A), 2.0, 0.0, cp->e_2_b);
		md->A_evo[dump_id] = md->A;
	}
}

void delete_weibull_data(MainData * md)
{
	delete[] md->A_evo;
}