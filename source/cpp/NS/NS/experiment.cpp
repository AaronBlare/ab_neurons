#include "experiments.h"

void basic_exp(RunParam * rp, ConfigParam * cp)
{
	for (int f_in_id = 0; f_in_id < rp->f_in_num; f_in_id++)
	{
		cp->e_1_2_f_in = rp->f_in_start + double(f_in_id) * rp->f_in_shift;

		for (int b_id = 0; b_id < rp->b_num; b_id++)
		{
			cp->e_2_b = rp->b_start + double(b_id) * rp->b_shift;

			for (int seed = rp->seed_start; seed < rp->seed_start + rp->seed_num; seed++)
			{
				cp->seed = seed;

				cout << "e_1_2_f_in = " << cp->e_1_2_f_in << endl;
				cout << "e_2_b = " << cp->e_2_b << endl;
				cout << "seed = " << cp->seed << endl;

				MainData * md = new MainData();

				NewDelBehavior * ndb;
				RightPartBehavior * rpb;
				PropagationBehavior * pb;

				if (rp->system == 0)
				{
					ndb = new SimpleNewDelBehaviour();
					rpb = new SimpleRightPartBehaviour();
					pb = new SimplePropagationBehavior();
				}
				else if (rp->system == 1)
				{
					ndb = new FullNewDelBehaviour();
					rpb = new FullRightPartBehaviour();
					pb = new FullPropagationBehavior();
				}
				else
				{
					stringstream msg;
					msg << "Error: Wrong system value: " << rp->system << endl;
					Error(msg.str());
				}

				Processor * proc = new Processor(rp, cp, md);

				proc->set_newdel_behaviour(ndb);
				proc->set_right_part_behaviour(rpb);
				proc->set_propagation_behaviour(pb);

				proc->process();

				if (md->size_env > 0)
				{
					string fn_data_env = rp->path + "data_env" + file_name_suffix(rp, cp, 4);
					write_2d_double_data(fn_data_env, md->data_env_evo, md->size_env, md->size_evo, 16, 0);
				}

				calc_f_out(rp, cp, md);

				for (int n_id = 0; n_id < cp->nn; n_id++)
				{
					string fn_data_neu = rp->path + "data_neu_" + to_string(n_id) + file_name_suffix(rp, cp, 4);
					write_2d_double_data(fn_data_neu, md->data_neu_evo[n_id], md->size_neu, md->size_evo, 16, 0);

					string fn_time = rp->path + "time_" + to_string(n_id) + file_name_suffix(rp, cp, 4);
					write_double_data(fn_time, md->time_evo, md->size_evo, 16, 0);

					string fn_f_out = rp->path + "f_out_" + to_string(n_id) + file_name_suffix(rp, cp, 4);
					write_double_data(fn_f_out, &(md->f_out[n_id]), 1, 16, 0);
				}

				proc->clear();

				delete ndb;
				delete rpb;
				delete pb;
			}
		}
	}
}


void weibull_exp(RunParam * rp, ConfigParam * cp)
{
	for (int f_in_id = 0; f_in_id < rp->f_in_num; f_in_id++)
	{
		cp->e_1_2_f_in = rp->f_in_start + double(f_in_id) * rp->f_in_shift;

		for (int b_id = 0; b_id < rp->b_num; b_id++)
		{
			cp->e_2_b = rp->b_start + double(b_id) * rp->b_shift;

			for (int seed = rp->seed_start; seed < rp->seed_start + rp->seed_num; seed++)
			{
				cp->seed = seed;

				cout << "e_1_2_f_in = " << cp->e_1_2_f_in << endl;
				cout << "e_2_b = " << cp->e_2_b << endl;
				cout << "seed = " << cp->seed << endl;

				string fn_A = rp->path + "A" + file_name_suffix(rp, cp, 4);

				MainData * md = new MainData();

				init_weibull_data(rp, cp, md);

				weibull_dist(rp, cp, md);

				write_double_data(fn_A, md->A_evo, md->size_evo, 16, 0);

				delete_weibull_data(md);
			}
		}
	}
}