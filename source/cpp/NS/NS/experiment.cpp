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

				string fn_data = rp->path + "data" + file_name_suffix(rp, cp, 4);
				string fn_time = rp->path + "time" + file_name_suffix(rp, cp, 4);
				string fn_I_pre = rp->path + "I_pre" + file_name_suffix(rp, cp, 4);

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

				delete ndb;
				delete rpb;
				delete pb;

				write_2d_double_data(fn_data, md->data_evo, md->size, md->size_evo, 16, 0);
				write_double_data(fn_time, md->time_evo, md->size_evo, 16, 0);
				write_double_data(fn_I_pre, md->I_pre_evo, md->size_evo, 16, 0);

				calc_f_out(rp, cp, md);
				string fn_f_out = rp->path + "f_out" + file_name_suffix(rp, cp, 4);
				write_double_data(fn_f_out, &(md->f_out), 1, 16, 0);

				proc->clear();
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