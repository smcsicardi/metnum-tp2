CC=g++
CFLAGS=-Wall -Wpedantic -O2 -std=c++11
SOURCES=$(wildcard src/lib/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tp2
KFOLD=kfold

all: $(SOURCES) $(EXECUTABLE)

rebuild: clean all

$(KFOLD): src/kfold.cpp $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) src/kfold.cpp -o $@

$(EXECUTABLE): src/main.cpp $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) src/main.cpp -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
	rm $(EXECUTABLE)
	rm $(TEST)
