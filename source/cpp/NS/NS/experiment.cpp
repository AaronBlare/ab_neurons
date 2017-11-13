#include "experiments.h"

void basic_exp(RunParam &rp, ConfigParam &cp)
{
	for (int f_in_id = 0; f_in_id < rp.f_in_num; f_in_id++)
	{
		cp.e_1_2_f_in = rp.f_in_start + double(f_in_id) * rp.f_in_shift;

		for (int b_id = 0; b_id < rp.b_num; b_id++)
		{
			cp.e_2_b = rp.b_start + double(b_id) * rp.b_shift;

			for (int seed = rp.seed_start; seed < rp.seed_start + rp.seed_num; seed++)
			{
				cp.seed = seed;

				cout << "e_1_2_f_in = " << cp.e_1_2_f_in << endl;
				cout << "e_2_b = " << cp.e_2_b << endl;
				cout << "seed = " << cp.seed << endl;

				string fn_data = rp.path + "data" + file_name_suffix(rp, cp, 4);
				string fn_time = rp.path + "time" + file_name_suffix(rp, cp, 4);
				string fn_I_pre = rp.path + "I_pre" + file_name_suffix(rp, cp, 4);

				MainData md;

				init_main_data(rp, cp, md);
				init_cond(rp, cp, md);

				propagation(rp, cp, md);

				write_2d_double_data(fn_data, md.data_evo, md.size, md.size_evo, 16, 0);
				write_double_data(fn_time, md.time_evo, md.size_evo, 16, 0);
				write_double_data(fn_I_pre, md.I_pre_evo, md.size_evo, 16, 0);

				delete_main_data(md);
			}
		}
	}
}
