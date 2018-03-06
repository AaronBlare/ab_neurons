#pragma once
#include "config.h"
#include "utils.h"
#include "data.h"
#include "rightparter.h"

class PropagationBehavior
{
public:
	virtual void propagate(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb) const = 0;
};

class SimplePropagationBehavior : public PropagationBehavior
{
public:
	virtual void propagate(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb) const;
};

class FullPropagationBehavior : public PropagationBehavior
{
public:
	virtual void propagate(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb) const;
};

void rk_step(ConfigParam * cp, MainData * md, RightPartBehavior * rpb, double * impulses);

void update_max_min(ConfigParam * cp, MainData * md);

void int_second(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb, int sec_id, double * impulses);