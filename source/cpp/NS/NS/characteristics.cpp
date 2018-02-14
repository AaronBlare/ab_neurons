#include "characteristics.h"

struct greaters {
	bool operator()(const pair<pair<double, double>, int>& a, const pair<pair<double, double>, int>& b) const
	{
		return a.first.first < b.first.first;
	}
};

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
		vector< pair<pair<double, double>, int> > global(md->thr_crosses[0]);

		for (int n_id = 1; n_id < cp->nn; n_id++)
		{
			vector< pair<pair<double, double>, int> > global_copy(global);
			global.clear();
			global.resize(global_copy.size() + md->thr_crosses[n_id].size());
			merge(global_copy.begin(), global_copy.end(), md->thr_crosses[n_id].begin(), md->thr_crosses[n_id].end(), global.begin(), greaters());
			global_copy.clear();
		}


	}
}