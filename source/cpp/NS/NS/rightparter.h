#pragma once
#include "config.h"
#include "data.h"

class RightPartBehavior
{
public:
	virtual void set_right_part() const = 0;
};

class SimpleRightPartBehaviour : public RightPartBehavior
{
public:
	virtual void set_right_part() const;
};

class FullRightPartBehaviour : public RightPartBehavior
{
public:
	virtual void set_right_part() const;
};

void (*right_part)(ConfigParam *, MainData *, double *, double *, double, double) = NULL;

void right_part_simple(ConfigParam * cp, MainData * md, double * ks, double * x, double time, double impulse);

void right_part_full(ConfigParam * cp, MainData * md, double * ks, double * x, double time, double impulse);
