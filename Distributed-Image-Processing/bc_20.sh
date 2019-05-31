#!/bin/bash

#BSUB -e jer-%J-20.err.log
#BSUB -o jer-%J-20.out.log
#BSUB -J jer-20.job
#BSUB -q normal
#BSUB -n 20
##BSUB -R span[ptile=10]
module purge 
module load openmpi/1.8.8
module load numa/2.0.11
#module load cuda/8.0
cd /home/HPC-YT-JAN-MAY-2109/BRYAN-GOMEZ/lab_dip
mpirun -np 20 dip.x 1 imgs.txt 
