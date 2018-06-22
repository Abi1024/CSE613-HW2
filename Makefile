SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
HEADERS := $(wildcard *.h)
HD_OBJS := $(HEADERS:.h=.o)
TARGETS := main

CFLAGS=-Wall -O2 -std=c++11 -g
CC=g++
LDADD=-fopenmp

all: $(TARGETS)
.PHONY : all

$(OBJECTS) : %.o : %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDADD)

$(TARGETS) : % : %.o $(HD_OBJS)
	$(CC) -o $@ $^ $(LDADD)

clean:
	rm $(TARGETS) $(OBJECTS)
