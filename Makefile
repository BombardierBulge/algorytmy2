CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = main.exe
SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp)

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)