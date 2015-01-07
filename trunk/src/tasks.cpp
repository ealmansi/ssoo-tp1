#include <cstdlib>
#include <ctime>
#include <set>

#include "tasks.h"

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

void TaskConsola(int pid, vector<int> params) { // params: n, bmin y bmax
	int& n = params[0];
	int& bmin = params[1];
	int& bmax = params[2];
	for (int i = 0; i < n; ++i)
		uso_IO(pid, rand() % (bmax - bmin + 1) + bmin);
}

void TaskBatch(int pid, vector<int> params) { // params: total_cpu, cant_bloqueos
	int& total_cpu = params[0];
	int& cant_bloqueos = params[1];

	set<int> bloqueos;
	while	(bloqueos.size() < cant_bloqueos) {
		bloqueos.insert(rand() % total_cpu);
	}

	int anterior = -1;
	set<int>::const_iterator it;
	for (it = bloqueos.begin(); it != bloqueos.end(); ++it) {
		uso_CPU(pid, *it - (anterior + 1));
		uso_IO(pid, 1);
		anterior = *it;
	}
	uso_CPU(pid, total_cpu - (anterior + 1));
}

void tasks_init(void) {

	srand(10);

	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskBatch, 2);
}
