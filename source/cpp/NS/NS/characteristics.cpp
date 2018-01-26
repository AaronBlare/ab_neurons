#include "characteristics.h"

void calc_f_out(RunParam * rp, ConfigParam * cp, MainData * md)
{
	cout << "num_thr_cross_Vpost: " << md->num_thr_cross_Vpost << endl;
	double mean_freq = double(md->num_thr_cross_Vpost) / (double(cp->ns) / 1000.0);
	md->f_out = mean_freq;
}