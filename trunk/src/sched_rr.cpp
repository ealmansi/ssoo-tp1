#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

#define DEBUG()	{std::cout << __LINE__ << std::endl;}

using namespace std;

SchedRR::SchedRR(vector<int> argn) :
	cores_qty(argn[0]),
	core_quantum(argn.begin() + 1, argn.begin() + 1 + cores_qty),
	core_remaining_quantum(core_quantum)
{ }

SchedRR::~SchedRR() {
}

void SchedRR::load(int pid) {
	// llegó una tarea nueva
	q.push(pid);
}

void SchedRR::unblock(int pid) {
	// La tarea pid dejó de estar bloqueada. Se agrega al final de la cola.
	q.push(pid);
}

int SchedRR::next(int cpu) {
	// Si la cola está vacía, ejecuto la tarea IDLE
	if (q.empty())
		return IDLE_TASK;
	
	// Obtengo el proximo pid de la cola ready
	int sig = q.front(); q.pop();
	core_remaining_quantum[cpu] = core_quantum[cpu];
	return sig;
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	// Si la tarea en ejecución es la tarea IDLE, o si la tarea actual
	// terminó o ejecutó una llamada bloqueante, sigue la próxima
	if (current_pid(cpu) == IDLE_TASK || m == BLOCK || m == EXIT)
		return next(cpu);

	// Reducimos la cantidad de ticks que le quedan a la tarea actual
	int pid = current_pid(cpu);
	--core_remaining_quantum[cpu];

	// Si la tarea actual ha consumido su quantum, la reinsertamos al final de la cola y sigue la proxima
	if (core_remaining_quantum[cpu] == 0) {
		q.push(pid);
		return next(cpu);
	}
	
	// Continúa ejecutando la tarea actual
	return pid;
}
