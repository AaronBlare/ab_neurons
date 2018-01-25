#pragma once
#include "config.h"
#include "data.h"
#include "newdeler.h"
#include "rightparter.h"
#include "propagator.h"


class Processor
{
private:
	RunParam * rp;
	ConfigParam * cp;
	MainData * md;

	NewDelBehavior * ndb;
	RightPartBehavior * rpb;
	PropagationBehavior * pb;
	

public:
	Processor(RunParam * rp, ConfigParam * cp, MainData * md);

	void set_newdel_behaviour(NewDelBehavior* ndb);

	void set_right_part_behaviour(RightPartBehavior * rpb);

	void set_propagation_behaviour(PropagationBehavior * pb);

	void process();

	void clear();
};