CC = g++
LD = g++

CCFLAGS  = -std=c++17
#CCFLAGS += -Wall
CCFLAGS += -Wno-deprecated-declarations
CCFLAGS += -g
CCFLAGS += -O0
CCFLAGS += -Iinclude -Iinclude/lib

OBJECTS += build/main.o
OBJECTS += build/render.o

build/%.o: src/%.cpp include/%.h
	$(CC) $< -c $(CCFLAGS) -o $@

build: $(OBJECTS)
	$(LD) $^ $(LDFLAGS) -o build/main

clean:
	rm -f $(OBJECTS)

run: build
	./build/main

crun: clean run
