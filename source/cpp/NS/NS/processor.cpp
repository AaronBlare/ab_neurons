#include "processor.h"

Processor::Processor(RunParam * rp, ConfigParam * cp, MainData * md)
{
	this->rp = rp;
	this->cp = cp;
	this->md = md;
}

void Processor::set_newdel_behaviour(NewDelBehavior * ndb)
{
	this->ndb = ndb;
}

void Processor::set_right_part_behaviour(RightPartBehavior * rpb)
{
	this->rpb = rpb;
}

void Processor::set_propagation_behaviour(PropagationBehavior * pb)
{
	this->pb = pb;
}

void Processor::process()
{
	ndb->init_data(rp, cp, md);
	pb->propagate(rp, cp, md, rpb);
}


void Processor::clear()
{
	ndb->free_data(rp, cp, md);
}