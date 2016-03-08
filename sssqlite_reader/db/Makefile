CXX = g++
CXXFLAGS = -g -Wall -fPIC
OBJS = DBWorker.o 
LDFLAGS += -shared -Wl,-soname
LDLIBS += -L/usr/lib64 -lsqlite3

TARGET = libDBWorker.so

$(TARGET): $(OBJS) 
	$(CXX) $(LDFLAGS),$(TARGET) -o $(TARGET) $(OBJS) $(LDLIBS)
	if [ ! -d ../lib ]; then mkdir ../lib; fi
	mv $(TARGET) ../lib

$(OBJS): %.o: %.cxx %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 


clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f ../lib/$(TARGET)
