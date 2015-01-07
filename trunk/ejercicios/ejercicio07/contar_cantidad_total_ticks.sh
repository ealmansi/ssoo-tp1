#!/bin/bash

for f in tareas_ej7_$1*.data
do
  printf "$(cat $f | grep "^CPU" | tail -1 | sed 's/CPU \([0-9][0-9]*\).*/\1/')\t\t$f\n"
done