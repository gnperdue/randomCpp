CPPFLAGS  = -O3 -Wall -Werror -fPIC
CPPFLAGS += -std=c++1y -stdlib=libc++
LDFLAGS   = -stdlib=libc++
LDLIBS =
INCLUDE =
CXX = clang++

all: maptest

%.o: %.cxx
	$(CXX) $(INCLUDE) $(CPPFLAGS) $(LDLIBS) -c $< -o $@ #compile

maptest: maptest.o
	$(CXX) $(INCLUDE) $(CPPFLAGS) $(LDLIBS) $^ -o $@    #link

clean:
	rm -f maptest.o
	rm -f maptest
