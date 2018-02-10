#pragma once
#include "config.h"
#include "data.h"

class RightPartBehavior
{
public:
	virtual void right_part(ConfigParam * cp, MainData * md, int sub_step, double * impulses) const = 0;
	virtual void update_arg(ConfigParam * cp, MainData * md, int sub_step, double coeff) const = 0;
	virtual void rk_final(ConfigParam * cp, MainData * md, double step) const = 0;
	virtual void set_init_args(ConfigParam * cp, MainData * md) const = 0;
};

class SimpleRightPartBehaviour : public RightPartBehavior
{
public:
	virtual void right_part(ConfigParam * cp, MainData * md, int sub_step, double * impulses) const;
	virtual void update_arg(ConfigParam * cp, MainData * md, int sub_step, double coeff) const;
	virtual void rk_final(ConfigParam * cp, MainData * md, double step) const;
	virtual void set_init_args(ConfigParam * cp, MainData * md) const;
};

class FullRightPartBehaviour : public RightPartBehavior
{
public:
	virtual void right_part(ConfigParam * cp, MainData * md, int sub_step, double * impulses) const;
	virtual void update_arg(ConfigParam * cp, MainData * md, int sub_step, double coeff) const;
	virtual void rk_final(ConfigParam * cp, MainData * md, double step) const;
	virtual void set_init_args(ConfigParam * cp, MainData * md) const;
};

void right_part_common(ConfigParam * cp, MainData * md, int sub_step, double * impulses);
void update_arg_common(ConfigParam * cp, MainData * md, int sub_step, double coeff);
void rk_final_common(ConfigParam * cp, MainData * md, double step);
void set_init_args_common(ConfigParam * cp, MainData * md);