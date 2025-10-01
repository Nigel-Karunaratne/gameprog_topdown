# PLATFORM = linux
EXEC_NAME := main

CXX := g++

INCLUDE_DIRS := -I ./include/ -I ./ -I ./vendor/raylib -I ./vendor/rlcpp
LIB_DIRS := -L ./vendor/raylib

LIBS := -lraylib

ifeq ($(OS),Windows_NT)
	LIBS += -lgdi32 -lwinmm
	EXEC_NAME := main.exe
else
	LIBS += -lGL -lm -lpthread -ldl -lrt -lX11
endif


all: bin/ src/main.cpp
	$(CXX) src/main.cpp -o bin/$(EXEC_NAME) $(LIB_DIRS) $(LIBS) $(INCLUDE_DIRS)

clean:
	rm bin/$(EXEC_NAME)

bin/:
	mkdir bin

install_deps:
	mkdir -p vendor
	mkdir -p vendor/imgui
	mkdir -p vendor/raylib
	mkdir -p vendor/rlcpp
	mkdir -p vendor/rlimgui

	