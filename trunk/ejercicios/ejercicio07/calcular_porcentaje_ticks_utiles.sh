#!/bin/bash

for f in tareas_ej7_$1*.data
do
  cant_ticks_utiles=$(cat $f | grep "^CPU" | wc -l)
  cant_total_ticks=$(cat $f | grep "^CPU" | tail -1 | sed 's/CPU \([0-9][0-9]*\).*/\1/')
  pcj=$(echo "$cant_ticks_utiles $cant_total_ticks $1" | awk '{printf "%.2f \n", $1/$2/$3}')
  printf "${pcj}\t\t${f}\n"
done