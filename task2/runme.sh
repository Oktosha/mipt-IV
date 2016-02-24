#!/bin/bash

MAX_N_THREADS=10
ARR_SIZE=10000000
function run {
	printf "     %2d |" $1
	echo "${ARR_SIZE} $1 0" | ./summator 
	printf "|"
	echo "${ARR_SIZE} $1 1" | ./summator 
	printf "\n"
}

make
printf "threads |     simple |        sin\n"
for i in $(seq 1 $MAX_N_THREADS);
	do
		run ${i}
	done