#!/bin/bash

EJECUTABLE=../../src/simusched
GRAFICADOR=../../src/graphsched.py

$EJECUTABLE tareas_ej2.tsk 1 1 1 SchedFCFS | python $GRAFICADOR > tareas_ej2_1_1_1_fcfs.png
$EJECUTABLE tareas_ej2.tsk 2 1 1 SchedFCFS | python $GRAFICADOR > tareas_ej2_2_1_1_fcfs.png
$EJECUTABLE tareas_ej2.tsk 3 1 1 SchedFCFS | python $GRAFICADOR > tareas_ej2_3_1_1_fcfs.png