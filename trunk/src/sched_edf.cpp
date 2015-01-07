#include "sched_edf.h"

using namespace std;

SchedEDF::SchedEDF(vector<int> argn):contador(0){//, running(argn[0]){
	Job j(IDLE_TASK,FREE);
	for(unsigned i=0; i<argn[0];i++){
		running.push_back(j);
	}
}

SchedEDF::~SchedEDF() {
}

void SchedEDF::load(int pid) {
  load(pid,0);
}

void SchedEDF::load(int pid,int deadline) {
	if(contador!=0){
		int cant=contador/running.size();//dividimos por la cantidad de cpus para calcular la cantidad de ciclos de reloj transcurridos
		actualizar(cant);
	}
	Job a(pid,deadline); 
	ready.push_back(a); //agregamos la nueva tarea
	sort(ready.begin(),ready.end(),comparar); // reordenamos las tareas pendientes
}

void SchedEDF::unblock(int pid) {
	for(unsigned i=0; i<blocked.size();i++){
		if(blocked[i].pid==pid){
			ready.push_back(blocked[i]);//agregamos la tarea a listas
			sort(ready.begin(),ready.end(),comparar); // reordenamos las tareas pendientes
			blocked.erase(blocked.begin()+i); //borramos la tarea de blocked
		}
		break;
	}
}

int SchedEDF::tick(int cpu, const enum Motivo m) {
	if(m==TICK){ 
		contador++;	
	}
	else if(m==BLOCK){
		blocked.push_back(running[cpu]);//agregamos la tarea a blocked
		running[cpu].pid=IDLE_TASK; //quitamos la tarea de running
		running[cpu].deadline=FREE;
	}
	else{ //caso exit
		running[cpu].pid=IDLE_TASK; //quitamos la tarea de running
		running[cpu].deadline=FREE;			
	}
	return proximo(cpu); //retornamos el proximo pid a ejecutar
}

void SchedEDF::actualizar(int cant){
	contador=0; //reseteamos el contador
	for (unsigned i=0; i< ready.size(); i++){
		ready[i].deadline-= cant;	// restamos a deadline los ciclos transcurridos
	}
	for (unsigned i=0; i< blocked.size(); i++){
		blocked[i].deadline-= cant;	// restamos a deadline los ciclos transcurridos
	}
	for(unsigned i=0; i < running.size(); i++){
		running[i].deadline-=cant;	//restamos a deadline los ciclos transcurridos
	}
}

int SchedEDF::proximo(int cpu){
	int p = running[cpu].pid;
	if(p!=IDLE_TASK){
		if(!ready.empty()){ //si tengo procesos pendientes
			Job j=ready.front();
			int d=running[0].deadline;
			for(unsigned i=0;i<running.size();i++){
				if(running[i].deadline > d){
					d=running[i].deadline;//buscamos la tarea en ejecucion con mayor deadline
				}
			}
			if(running[cpu].deadline <= j.deadline || running[cpu].deadline < d){
				return p; //el pid ejecutandose es el con menos deadline || hay otra tarea ejecutandose con mayor deadline, para evitar cambios de contexto innecesarios cambiaremos la tarea cuando llegue el tick del core de esa tarea
			}
			else{
				ready.push_back(running[cpu]); //agregamos la tarea corriendo a ready
				running[cpu]=j; //cambiamos la tarea corriendo
				ready.erase(ready.begin()); //borramos la tarea de ready
				sort(ready.begin(),ready.end(),comparar); // reordenamos las tareas pendientes
				return j.pid;
			}
		}
		else{	//si no hay procesos pendientes
			return current_pid(cpu); //retornamos el pid ejecutandose
		}
	}
	else{	//se esta ejecutando la tarea idle || blockeada || terminada
		if(!ready.empty()){ //si tengo procesos pendientes
			running[cpu]=ready.front(); //cambiamos la tarea corriendo
			ready.erase(ready.begin());	//borramos la tarea de ready
			return running[cpu].pid;
		}
		else{ //si no hay procesos pendientes
			return IDLE_TASK;
		}
	}
}

bool comparar(Job j1, Job j2){
	return (j1.deadline < j2.deadline); //ordenamos por deadline
}
