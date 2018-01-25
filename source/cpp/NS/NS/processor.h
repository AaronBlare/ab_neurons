#pragma once
#include "config.h"
#include "data.h"
#include "newdeler.h"

class Processor
{
private:
	RunParam * rp;
	ConfigParam * cp;
	MainData * md;

	NewDelBehavior * ib;
	

public:
	Processor(RunParam * rp, ConfigParam * cp, MainData * md);

	void set_init_behaviour(NewDelBehavior* ib);

	void process();
};