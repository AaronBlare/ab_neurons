#include "characteristics.h"

void calc_f_out(RunParam * rp, ConfigParam * cp, MainData * md)
{
	for (int n_id = 0; n_id < cp->nn; n_id++)
	{
		cout << "num_thr_cross_Vpost for " << n_id << " neuron: " << md->num_thr_cross_Vpost[n_id] << endl;
		double mean_freq = double(md->num_thr_cross_Vpost[n_id]) / (double(cp->ns) / 1000.0);
		md->f_out[n_id] = mean_freq;
	}
}

void calc_eta(RunParam * rp, ConfigParam * cp, MainData * md)
{
	if (cp->is_eta_calc > 0)
	{

	}
}