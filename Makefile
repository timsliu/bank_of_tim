# Compiler flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror

all: economy

# variables
OBJS = client.o bank.o economy.o

# dependencies
client.o: client.cpp client.h

bank.o: bank.cpp bank.h client.h

economy.o: economy.cpp bank.h client.h

# build rules

economy: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f test *.o *~

.PHONY: all clean

