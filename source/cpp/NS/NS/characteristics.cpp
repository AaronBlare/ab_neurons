#include "characteristics.h"
#include <set> 
#include <deque>

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

		while (global.size() > 0)
		{
			double limit = global[0].first.second + cp->eta_window;
			
			vector<int> part_neu;
			part_neu.push_back(global[0].second);

			vector<int> indexes_to_delete;

			for (int index = 1; index < global.size(); index++)
			{
				if (global[index].first.first > limit)
				{
					break;
				}
				else
				{
					vector<int>::iterator it = find(part_neu.begin(), part_neu.end(), global[index].second);
					if (it == part_neu.end())
					{
						part_neu.push_back(global[index].second);
						indexes_to_delete.push_back(index);
					}
				}
			}

			if (part_neu.size() == cp->nn)
			{
				md->num_sync_spikes++;
				
				if (indexes_to_delete.size() > 0)
				{
					for (int itd = indexes_to_delete.size() - 1; itd >= 0; itd--)
					{
						global.erase(global.begin() + indexes_to_delete[itd]);
					}
				}
			}
			global.erase(global.begin());
		}

		double sum_spikes = 0.0;
		for (int n_id = 0; n_id < cp->nn; n_id++)
		{
			sum_spikes += double(md->thr_crosses[n_id].size());
		}

		md->eta = double(cp->nn) * double(md->num_sync_spikes) / sum_spikes;

		cout << "eta: " << md->eta << endl;
	}
}