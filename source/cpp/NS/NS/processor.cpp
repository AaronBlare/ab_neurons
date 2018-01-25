#include "processor.h"

Processor::Processor(RunParam * rp, ConfigParam * cp, MainData * md)
{
	this->rp = rp;
	this->cp = cp;
	this->md = md;
}

void Processor::set_init_behaviour(NewDelBehavior * ib)
{
	this->ib = ib;
}

void Processor::process()
{
}
