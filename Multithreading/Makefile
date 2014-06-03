CC=g++
CFLAGS= -c -I. -std=c++11 -pthread -Wl,--no-as-needed
LDFLAGS= -I. -lm -pthread -lpthread
SOURCES= MT.cpp SpinLock.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Cpp

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o 
	rm -f $(EXECUTABLE)
