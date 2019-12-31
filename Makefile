# Revision History
# 12/29/19    Tim Liu    added economy.o and dependencies
# 12/30/19    Tim Liu    fixed bug where economy.o was missing economy.h dependency

# Compiler flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror

all: economy

# variables
OBJS = client.o bank.o economy.o

# dependencies
client.o: client.cpp client.h

bank.o: bank.cpp bank.h client.h

economy.o: economy.cpp bank.h client.h economy.h

# build rules
economy: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f test *.o *~

.PHONY: all clean

