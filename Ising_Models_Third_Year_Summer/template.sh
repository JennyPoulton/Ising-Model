#!/bin/bash
#$ -l h_rt=100:00:00
#$ -l mem=1.0G
#$ -m bea
#$ -M pha10jp@shef.ac.uk
#$ -o output.txt
#$ -e error.txt
#$ -N Test1

mkdir Test1
cp Main.cpp Test1/
cp System.cpp Test1/
cp Particle.cpp Test1/
cp System.h Test1/
cp Particle.h Test1/
cd Test1/
g++ Main.cpp -o runMain
./runMain

