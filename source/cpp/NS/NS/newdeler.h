#pragma once
#include "config.h"
#include "data.h"

class NewDelBehavior
{
public:
	virtual void init_data(RunParam * rp, ConfigParam * cp, MainData * md) const = 0;
	virtual void free_data(RunParam * rp, ConfigParam * cp, MainData * md) const = 0;
};

class SimpleNewDelBehaviour : public NewDelBehavior
{
public:
	virtual void init_data(RunParam * rp, ConfigParam * cp, MainData * md) const;
	virtual void free_data(RunParam * rp, ConfigParam * cp, MainData * md) const;
};

class FullNewDelBehaviour : public NewDelBehavior
{
public:
	virtual void init_data(RunParam * rp, ConfigParam * cp, MainData * md) const;
	virtual void free_data(RunParam * rp, ConfigParam * cp, MainData * md) const;
};

void init_all_data(RunParam * rp, ConfigParam * cp, MainData * md, int size);

void init_model_data(RunParam * rp, ConfigParam * cp, MainData * md, int size);

void init_random_data(RunParam * rp, ConfigParam * cp, MainData * md);

void init_evo_data(RunParam * rp, ConfigParam * cp, MainData * md);

void init_propagation_data(RunParam * rp, ConfigParam * cp, MainData * md);

void init_start(RunParam * rp, ConfigParam * cp, MainData * md);

void free_all_data(MainData * md);