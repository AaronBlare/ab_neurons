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

void upd_arg(int size, double * x_arg, double * x, double * ks, double coeff);

void rk_final(int size, double * x, double * k1s, double * k2s, double * k3s, double * k4s, double step);

void rk_step(ConfigParam * cp, MainData * md, RightPartBehavior * rpb, double impulse);

void int_second(RunParam * rp, ConfigParam * cp, MainData * md, RightPartBehavior * rpb, int sec_id, double impulse);