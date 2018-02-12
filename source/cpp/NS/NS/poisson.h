#pragma once
#include "config.h"
#include "utils.h"
#include "data.h"

void init_poisson_data(RunParam * rp, ConfigParam * cp, MainData * md);
void poisson_dist(RunParam * rp, ConfigParam * cp, MainData * md);
void delete_poisson_data(MainData * dt);