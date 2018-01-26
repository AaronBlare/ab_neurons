#pragma once
#include "config.h"
#include "data.h"

class RightPartBehavior
{
public:
	virtual void right_part(ConfigParam * cp, MainData * md, double * ks, double * x, double time, double impulse) const = 0;
};

class SimpleRightPartBehaviour : public RightPartBehavior
{
public:
	virtual void right_part(ConfigParam * cp, MainData * md, double * ks, double * x, double time, double impulse) const;
};

class FullRightPartBehaviour : public RightPartBehavior
{
public:
	virtual void right_part(ConfigParam * cp, MainData * md, double * ks, double * x, double time, double impulse) const;
};
