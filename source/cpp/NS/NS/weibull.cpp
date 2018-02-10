#include "weibull.h"

void init_weibull_data(RunParam * rp, ConfigParam * cp, MainData * md)
{
	md->streams_w = new VSLStreamStatePtr[1];
	vslNewStream(&(md->streams_w[0]), VSL_BRNG_MCG31, 77778888);
	vslLeapfrogStream(md->streams_w[0], cp->seed, rp->max_num_seeds);

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
		double A = 0.0;
		vdRngWeibull(VSL_RNG_METHOD_WEIBULL_ICDF, md->streams_w[0], 1, &(A), 2.0, 0.0, cp->e_2_b);
		md->A_evo[dump_id] = A;
	}
}

void delete_weibull_data(MainData * md)
{
	delete[] md->A_evo;
}