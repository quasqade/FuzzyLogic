#Compiler to user
COMPILER=g++
#Compiler arguments
CFLAGS=-c -g -Wall
LDFLAGS=
SOURCES=main.cpp fuzzy_set.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):$(OBJECTS)
	$(COMPILER) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(COMPILER) $(CFLAGS) $< -o $@
