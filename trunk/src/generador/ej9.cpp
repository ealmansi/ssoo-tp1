#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <time.h>
#include <cstdlib>
#include <random>

using namespace std;

int main(int argc, char** argv){
	//Parametros:  1.cantidad de tareas, 2. cantidad maxima uso cpu
	if(argc != 3){
		cout << "Parametros:  1. cantidad de tareas, 2. cantidad maxima uso cpu" << endl;
		return 0;
	}
    // Cargo parámetros del test
    int cant_tareas = atoi(argv[1]);
    int max_cpu = atoi(argv[2]);
	int max_deadline=max_cpu*cant_tareas/3;
	vector<int>cpu (cant_tareas);
	vector<int>deadline (cant_tareas);

	//generamos los deadlines
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator (seed);
	uniform_int_distribution<int> deadlines(cant_tareas,max_deadline);
	for(unsigned i=0;i<deadline.size();i++){
		deadline[i]=deadlines(generator);
	}
	//ordenamos deadline
	sort(deadline.begin(), deadline.end());

	//generamos los ciclos de cpu
	uniform_int_distribution<int> ciclos(1,max_cpu);
	int sum_c=0;
	int c,t,f;
	for(unsigned i=0;i<cpu.size();i++){
		t=deadline[i];
		c=ciclos(generator);
		f=0;
		while((((float)c + (float)sum_c)/ (float)t)>=1){
			c=ciclos(generator);
			f++;
			if(f>10){ //no es posible una solución
				for(unsigned j=i;j<deadline.size();j++){//aumentamos el deadline
					deadline[j]+=5;	
				}
				t=deadline[i];
				f=0;
			}
		}
		cpu[i]=c;
		sum_c += c;
	}
	
	//generamos la salida aleatoriamente
	vector<int> out;
	for (int i=0; i<deadline.size(); ++i){
		out.push_back(i);
	}
	shuffle(out.begin(), out.end(), generator); 
	cout << "@0:" << endl;
	for(unsigned i=0;i<out.size();i++){
		int j=out[i];
		cout << "$" << deadline[j] << endl;
		cout << "TaskCPU " << cpu[j]-1 << endl;  //graphsched considera 0 como 1 ciclo
	}

	return 0;
}

