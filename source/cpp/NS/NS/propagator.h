#pragma once
#include "config.h"
#include "utils.h"
#include "data.h"
#include "rightparter.h"

class PropagatingBehavior
{
public:
	virtual void propagate(RunParam * rp, ConfigParam * cp, MainData * md) const = 0;
};

class SimplePropagatingBehavior : public PropagatingBehavior
{
public:
	virtual void propagate(RunParam * rp, ConfigParam * cp, MainData * md) const;
};

class FullPropagatingBehavior : public PropagatingBehavior
{
public:
	virtual void propagate(RunParam * rp, ConfigParam * cp, MainData * md) const;
};

void upd_arg(int size, double * x_arg, double * x, double * ks, double coeff);

void rk_final(int size, double * x, double * k1s, double * k2s, double * k3s, double * k4s, double step);

void rk_step(ConfigParam &cp, MainData &md, double impulse);

void int_second(RunParam &rp, ConfigParam &cp, MainData &md, int sec_id, double impulse);

void weibull_dist(RunParam &rp, ConfigParam &cp, MainData &md);

void calc_f_out(RunParam &rp, ConfigParam &cp, MainData &md);