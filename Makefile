# Makefile for Library Management System

CXX = g++
CXXFLAGS = -Iinclude -Wall
SRC = $(wildcard src/*.cpp)
OUT = LibrarySystem

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
