#include <algorithm>
#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) :
  cores_qty(argn[0]),
  core_q(cores_qty),
  core_quantum(argn.begin() + 1, argn.begin() + 1 + cores_qty),
  core_remaining_quantum(core_quantum)
{}

SchedRR2::~SchedRR2() 
{}

void SchedRR2::load(int pid) {
  // Asigno la tarea al core con menor carga
  pid_core[pid] = minimum_load_core();

  // Se agrega la tarea al final de la cola de su core
  core_q[pid_core[pid]].push(pid);
}

int SchedRR2::minimum_load_core() {
  // Cuento la cantidad de tareas en estado running, blocked o ready por cada core
  vector<int> core_pid_count(cores_qty);
  for (map<int,int>::const_iterator i = pid_core.begin(); i != pid_core.end(); ++i)
    ++core_pid_count[i->second];
 
  // Elijo aquel que tiene menor cantidad de tareas
  return min_element(core_pid_count.begin(), core_pid_count.end()) - core_pid_count.begin();
}

void SchedRR2::unblock(int pid) {
  // La tarea pid dejó de estar bloqueada. Se agrega al final de la cola de su core
  core_q[pid_core[pid]].push(pid);
}

int SchedRR2::next(int cpu) {
  // Si la cola está vacía, ejecuto la tarea IDLE
  if (core_q[cpu].empty())
    return IDLE_TASK;
  
  // Obtengo el proximo pid de la cola ready del core
  int sig = core_q[cpu].front(); core_q[cpu].pop();
  core_remaining_quantum[cpu] = core_quantum[cpu];
  return sig;
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
  // Si la tarea en ejecución es la tarea IDLE, o si la tarea actual
  // ejecutó una llamada bloqueante, sigue la próxima
  if (current_pid(cpu) == IDLE_TASK || m == BLOCK)
    return next(cpu);

  // Si la tarea actual terminó, la elimino del directorio de tareas y sigue la próxima
  int pid = current_pid(cpu);
  if (m == EXIT) {
    pid_core.erase(pid);
    return next(cpu);
  }

  // Reducimos la cantidad de ticks que le quedan a la tarea actual
  --core_remaining_quantum[cpu];

  // Si la tarea actual ha consumido su quantum, la reinsertamos al final de la cola y sigue la proxima
  if (core_remaining_quantum[cpu] == 0) {
    core_q[cpu].push(pid);
    return next(cpu);
  }
  
  // Continúa ejecutando la tarea actual
  return pid;
}
