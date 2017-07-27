CXX = g++
CC = gcc
CFLAGS = -c
CXXFLAGS = -ldl -Wall -std=c++11 -lpthread
SQLFLAGS = -DSQLITE_THREADSAFE=0

OUTPUTBIN = main
OUTPUTDIR = ./build/
MKDIR = mkdir -p $(OUTPUTDIR)
OBJECTC = sqlite3.o
CSOURCES = sqlite3.c
CXXSOURCES = Main.cpp PeriodicScheduler.cpp Task.cpp Database.cpp

all: project

project: createdir sql compilecpp

createdir:
	$(MKDIR)

sql:
	$(CC) $(CSOURCES) $(SQLFLAGS) $(CFLAGS) -o $(OUTPUTDIR)$(OBJECTC)

compilecpp:
	$(CXX) $(OUTPUTDIR)$(OBJECTC) $(CXXSOURCES) $(CXXFLAGS) -o $(OUTPUTDIR)$(OUTPUTBIN)

clean:
	rm -rf $(OUTPUTDIR)
