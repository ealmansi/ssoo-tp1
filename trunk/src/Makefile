export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb -std=c++0x -Wno-sign-compare
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_edf.o
MAIN=simusched

VPATH= generador
DEP = $(GEN:=.cpp)
GEN= ej9

.PHONY: all
all: $(MAIN) $(GEN)

$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
sched_fcfs.o: sched_fcfs.cpp sched_fcfs.h basesched.h
sched_rr.o: sched_rr.cpp sched_rr.h basesched.h
sched_rr2.o: sched_rr2.cpp sched_rr2.h basesched.h
sched_edf.o: sched_edf.cpp sched_edf.h basesched.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

$(GEN): $(DEP) 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $(VPATH)/$@

.PHONY: clean
clean:
	rm -f $(OBJS) $(MAIN) $(VPATH)/$(GEN)

.PHONY: new
new: clean all
