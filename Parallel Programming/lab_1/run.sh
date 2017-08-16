#!/bin/bash

if [ $# -gt 0 ]; then
    mpirun -np $1 philosopher : -np 1 printer
else
    echo "Need an argument representing number of philosophers!"
fi