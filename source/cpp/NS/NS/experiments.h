#pragma once
#include "config.h"
#include "data.h"
#include "utils.h"
#include "characteristics.h"
#include "processor.h"
#include "weibull.h"
#include "poisson.h"

void basic_exp(RunParam * rp, ConfigParam * cp);

void weibull_exp(RunParam * rp, ConfigParam * cp);

void poisson_exp(RunParam * rp, ConfigParam * cp);
