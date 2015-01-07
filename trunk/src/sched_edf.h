#ifndef __SCHED_EDF__
#define __SCHED_EDF__

#include "basesched.h"
#include <algorithm>
#define FREE 999999

struct Job{
	int pid;
	int deadline;

	Job();	
	Job(int a, int b){
		pid=a;
		deadline=b;
	}
};

bool comparar(Job j1, Job j2);
	

class SchedEDF : public SchedBase {
  public:
    SchedEDF(std::vector<int> argn);
        ~SchedEDF();
    virtual void load(int pid);
    virtual void load(int pid, int deadline);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);

  private:
	void actualizar(int cant);
	int proximo(int cpu);

	int contador; //ciclos transcurridos desde ultima carga de tarea
	std::vector<Job> running; //tareas ejecutandose indexado por cpu
	std::vector<Job> ready; //tareas pendientes
	std::vector<Job> blocked; //tareas bloqueadas

};

#endif
