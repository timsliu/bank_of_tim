# Revision History
# 12/29/19    Tim Liu    added economy.o and dependencies
# 12/30/19    Tim Liu    fixed bug where economy.o was missing economy.h dependency
# 12/30/19    Tim Liu    added -fopenmp compiler flag

# Compiler flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -Xpreprocessor -fopenmp 
all: economy

# variables
OBJS = client.o bank.o economy.o multiqueue.o

# dependencies
client.o: client.cpp client.h

bank.o: bank.cpp bank.h client.h

economy.o: economy.cpp bank.h client.h economy.h

multiqueue.o: multiqueue.cpp multiqueue.h

# build rules
economy: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lomp

clean:
	rm -f test *.o *~

.PHONY: all clean

