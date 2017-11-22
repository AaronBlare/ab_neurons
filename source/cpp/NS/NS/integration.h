#pragma once
#include "config.h"
#include "utils.h"
#include "data.h"

void right_part(ConfigParam &cp, MainData &md, double * ks, double * x, double time, double impulse);

void upd_arg(int size, double * x_arg, double * x, double * ks, double coeff);

void rk_final(int size, double * x, double * k1s, double * k2s, double * k3s, double * k4s, double step);

void rk_step(ConfigParam &cp, MainData &md, double impulse);

void propagation(RunParam &rp, ConfigParam &cp, MainData &md);

void int_second(RunParam &rp, ConfigParam &cp, MainData &md, int sec_id, double impulse);

void weibull_dist(RunParam &rp, ConfigParam &cp, MainData &md);