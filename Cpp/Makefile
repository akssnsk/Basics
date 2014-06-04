CC=g++
CFLAGS= -c -I. -std=c++11 -pthread -Wl,--no-as-needed
LDFLAGS= -I. -lm -pthread -lpthread -lsasl2
SOURCES= stdafx.cpp Cpp.cpp CppStarter.cpp
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
