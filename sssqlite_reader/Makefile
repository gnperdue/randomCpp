CXX = g++
CXXFLAGS = -g -Wall -fPIC
INCLUDE += -I./db
LDLIBS += -L./lib -lDBWorker

BINARIES = dbmain
TARGETS = dbmain.o

all: $(BINARIES) 

debug: CXXFLAGS += -DDEBUG
debug: all

%.o: %.cxx
	$(CXX) $(INCLUDE) $(CXXFLAGS) $(LDLIBS) -c $< -o $@ #compile
    
dbmain: $(TARGETS)
	$(CXX) $(INCLUDE) $(CXXFLAGS) $(LDLIBS) $^ -o $@    #link
    
clean:
	rm -f $(BINARIES) $(TARGETS) 

