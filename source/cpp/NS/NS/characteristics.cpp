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

		string fn_f_out = rp->path + "f_out_" + to_string(n_id) + file_name_suffix(rp, cp, 4);
		write_double_data(fn_f_out, &(md->f_out[n_id]), 1, 16, 0);
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

		md->eta = double(cp->nn) * double(md->num_sync_spikes - 1) / sum_spikes;

		cout << "eta: " << md->eta << endl;

		string fn_eta = rp->path + "eta" + file_name_suffix(rp, cp, 4);
		write_double_data(fn_eta, &(md->eta), 1, 16, 0);

		double nss = double(md->num_sync_spikes - 1);
		string fn_nss = rp->path + "nss" + file_name_suffix(rp, cp, 4);
		write_double_data(fn_nss, &nss, 1, 16, 0);

		for (int n_id = 0; n_id < cp->nn; n_id++)
		{
			int num_spikes = md->thr_crosses[n_id].size() - 1;
			string fn_ns = rp->path + "num_spikes_" + to_string(n_id) + file_name_suffix(rp, cp, 4);
			write_int_data(fn_ns, &num_spikes, 1, 0);
		}

		if (cp->is_spikes_save > 0)
		{
			for (int n_id = 0; n_id < cp->nn; n_id++)
			{
				string fn_spikes_borders = rp->path + "spikes_borders_" + to_string(n_id) + file_name_suffix(rp, cp, 4);
				ofstream ofs = ofstream(fn_spikes_borders);
				if (ofs.is_open())
				{
					ofs << setprecision(16) << scientific;
					for (int i = 0; i < md->thr_crosses[n_id].size(); i++)
					{
						ofs << md->thr_crosses[n_id][i].first.first << " " << md->thr_crosses[n_id][i].first.second << endl;
					}

					ofs.close();
				}
			}
		}
	}
}