# !/bin/bash -i
#$ -S /bin/bash

# --- Mandatory qsub arguments
# Hardware requirements.
#$ -l h_rss=1000M,h_fsize=1000M,h_cpu=10:00:00,hw=x86_64

# --- Optional qsub arguments
# Change working directory - your job will be run from the directory
# that you call qsub in. So stdout and stderr will end up there .
# $ -cwd

# --- Job Execution
# For faster disk access copy files to / scratch first .
module load mkl

scratch=/scratch/yusipov/ab_neurons/$1
code_base=$HOME/Work/ab_neurons/source/cpp/NS/NS
mkdir -p $scratch
mkdir -p $1
cd $scratch
cp $1/config.txt .
cp $1/fin.txt .

# Execution - running the actual program .
# [ Remember : Don � t read or write to / home from here .]

echo " Running on $(hostname)"
echo " We are in $(pwd) "

cat config.txt
cat fin.txt
$code_base/NS.out

# Finish - Copy files back to your home directory , clean up .
cp -r $scratch/* $1 # Better use a subdirectory of $HOME .
rm -r $scratch/*
#cd
#rm - rf $scratch
