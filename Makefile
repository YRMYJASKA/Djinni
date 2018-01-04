C_FILES=src/main.cpp
C_FLAGS=-std=c++11 -lncurses -Wall -Wextra -Iinclude
CC=g++
NAME=out

include version.mk

.SILENT:

all: build

build: 
	$(CC) -o bin/$(NAME) $(C_FILES) $(C_FLAGS)

test:
	$(CC) $(C_FLAGS) -c tests/test_main.cpp
	$(CC) $(C_FLAGS) -o bin/tests test_main.o && bin/tests --success
	rm *.o

install:
	mkdir bin

# Echo the version numbers into version.h 
update_version: 
	echo "#pragma once" > src/include/version.h
	echo "#define VERSION_MAJOR $(VERSION_MAJOR)" >> src/include/version.h
	echo "#define VERSION_MINOR $(VERSION_MINOR)" >> src/include/version.h
	echo "#define VERSION_PATCH $(VERSION_PATCH)" >> src/include/version.h
	echo 'static const char* VERSION_STRING = "$(VERSION_STRING)";' >> src/include/version.h

clean:
	rm bin/*
