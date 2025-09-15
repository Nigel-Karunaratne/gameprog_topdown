EXEC_NAME := main

INCLUDE_DIRS := -I ./include/ -I ./ -I ./vendor/raylib
LIB_DIRS := -L ./vendor/raylib

LIB_LINUX := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LIB_WINDOWS := lraylib -lgdi32 -lwinmm


all: bin/ src/main.cpp
	g++ src/main.cpp -o bin/$(EXEC_NAME) $(LIB_DIRS) $(LIB_LINUX) $(INCLUDE_DIRS)

clean:
	rm bin/$(EXEC_NAME)

bin/:
	mkdir bin
