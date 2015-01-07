#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include <map>
#include "basesched.h"

class SchedRR2 : public SchedBase {
public:
	SchedRR2(std::vector<int> argn);
  ~SchedRR2();
	virtual void load(int pid);
	virtual void unblock(int pid);
	virtual int tick(int cpu, const enum Motivo m);

private:
  int minimum_load_core();
  int next(int cpu);

  int cores_qty;
  std::vector<std::queue<int> > core_q;
  std::vector<int> core_quantum;
  std::vector<int> core_remaining_quantum;
  std::map<int,int> pid_core;
};

#endif
