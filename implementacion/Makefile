CC=g++
CFLAGS=-Wall -Wpedantic -O2 -std=c++11
SOURCES=$(wildcard src/lib/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tp2
TEST=test
TESTCTR=testctr
TESTVELOCIDAD=testvelocidad

all: $(SOURCES) $(EXECUTABLE)

rebuild: clean all

$(TEST): src/test.cpp $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) src/test.cpp -o $@

$(TESTCTR): src/testCtr.cpp $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) src/testCtr.cpp -o $@

$(EXECUTABLE): src/main.cpp $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) src/main.cpp -o $@

$(TESTVELOCIDAD): src/testVelocidad.cpp $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) src/testVelocidad.cpp -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
