EXEC_NAME := main

INCLUDE_DIRS := -I ./include/ -I ./ -I ./vendor/raylib
LIB_DIRS := -L ./vendor/raylib

LIB := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: src/main.cpp
	g++ src/main.cpp -o $(EXEC_NAME) $(LIB_DIRS) $(LIB) $(INCLUDE_DIRS)

clean:
	rm $(EXEC_NAME)