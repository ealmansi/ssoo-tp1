#!/bin/bash

# Elegir al menos dos metricas diferentes. 
# Disenar un lote de tareas TaskBatch
#   igual uso de CPU, pero con diversas cantidades de bloqueos
# Simular con SchedRR, "variedad apropiada de valores de quantum"
# 1 costo de cambio de contexto, 2 el de migracion.
# variar la cantidad de nucleos de procesamiento
# concluir cual es el valor optimo de quantum a los efectos de cada una de las metricas elegidas.


EJECUTABLE=../../src/simusched
GRAFICADOR=../../src/graphsched.py

# 1 core
if [[ $1 -eq '1' ]]; then
  rm -f tareas_ej7_1*.png tareas_ej7_1*.data
  for(( i=1; i<=100; i=i+1 ))
  do
    quantum=$(printf "%02d" $i)
    $EJECUTABLE tareas_ej7.tsk 1 1 2 SchedRR $quantum > "tareas_ej7_1_1_2_rr_$quantum.data"
    cat "tareas_ej7_1_1_2_rr_$quantum.data" | python $GRAFICADOR > "tareas_ej7_1_1_2_rr_$quantum.png"
  done

# 2 cores
elif [[ $1 -eq '2' ]]; then
  rm -f tareas_ej7_2*.png tareas_ej7_2*.data
  for(( i=1; i<=100; i=i+1 ))
  do
    quantum1=$(printf "%02d" $i)
    quantum2=$(printf "%02d" $i)
    $EJECUTABLE tareas_ej7.tsk 2 1 2 SchedRR $quantum1 $quantum2 > "tareas_ej7_2_1_2_rr_${quantum1}_${quantum2}.data"
    cat "tareas_ej7_2_1_2_rr_${quantum1}_${quantum2}.data" | python $GRAFICADOR > "tareas_ej7_2_1_2_rr_${quantum1}_${quantum2}.png"
  done

# 3 cores
elif [[ $1 -eq '3' ]]; then
  rm -f tareas_ej7_3*.png tareas_ej7_3*.data
  for(( i=1; i<=100; i=i+1 ))
  do
    quantum1=$(printf "%02d" $i)
    quantum2=$(printf "%02d" $i)
    quantum3=$(printf "%02d" $i)
    $EJECUTABLE tareas_ej7.tsk 3 1 2 SchedRR $quantum1 $quantum2 $quantum3 > "tareas_ej7_3_1_2_rr_${quantum1}_${quantum2}_${quantum3}.data"
    cat "tareas_ej7_3_1_2_rr_${quantum1}_${quantum2}_${quantum3}.data" | python $GRAFICADOR > "tareas_ej7_3_1_2_rr_${quantum1}_${quantum2}_${quantum3}.png"
  done

# 4 cores
elif [[ $1 -eq '4' ]]; then
  rm -f tareas_ej7_4*.png tareas_ej7_4*.data
  for(( i=1; i<=100; i=i+1 ))
  do
    quantum1=$(printf "%02d" $i)
    quantum2=$(printf "%02d" $i)
    quantum3=$(printf "%02d" $i)
    quantum4=$(printf "%02d" $i)
    $EJECUTABLE tareas_ej7.tsk 4 1 2 SchedRR $quantum1 $quantum2 $quantum3 $quantum4 > "tareas_ej7_4_1_2_rr_${quantum1}_${quantum2}_${quantum3}_${quantum4}.data"
    cat "tareas_ej7_4_1_2_rr_${quantum1}_${quantum2}_${quantum3}_${quantum4}.data" | python $GRAFICADOR > "tareas_ej7_4_1_2_rr_${quantum1}_${quantum2}_${quantum3}_${quantum4}.png"
  done

else
  printf "Modo de uso: $0 <1|2|3|4>\n"
fi