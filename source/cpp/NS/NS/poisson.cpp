#include "poisson.h"

void init_poisson_data(RunParam * rp, ConfigParam * cp, MainData * md)
{
	md->streams_p = new VSLStreamStatePtr[1];
	vslNewStream(&(md->streams_p[0]), VSL_BRNG_MCG31, 77778888);
	vslLeapfrogStream(md->streams_p[0], cp->seed, rp->max_num_seeds);

	md->size_evo = cp->nd + 1;
	md->dump_shift = cp->ns / cp->nd;

	md->curr_dump_id = 0;

	md->H_x_evo = new int[md->size_evo];
	for (int dump_id = 0; dump_id < md->size_evo; dump_id++)
	{
		md->H_x_evo[dump_id] = 0;
	}
}

void poisson_dist(RunParam * rp, ConfigParam * cp, MainData * md)
{
	for (int dump_id = 0; dump_id < md->size_evo; dump_id++)
	{
		int H_x = 0;
		viRngPoisson(VSL_RNG_METHOD_POISSON_PTPE, md->streams_p[0], 1, &(H_x), cp->e_1_2_f_in[0]);
		md->H_x_evo[dump_id] = H_x;
	}
}

void delete_poisson_data(MainData * md)
{
	delete[] md->H_x_evo;
}