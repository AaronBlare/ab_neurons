#pragma once
#include "config.h"
#include "utils.h"
#include "data.h"


void init_lpn_data(ConfigParam &cp, MainData &md);
void init_cond_lpn(ConfigParam &cp, MainData &md);
void delete_lpn_data(MainData &md);
void calc_norm_lpn(MainData &md, int lpn_id);
void normalization_lpn(MainData &md, int lpn_id);
void scalar_mult_lpn(MainData &md, double * mults, int lpn_id, int lpn_id_tmp);
void sub_lpn(MainData &md, double* mults, int lpn_id, int lpn_id_tmp);
void gsorth_lpn(MainData &md);