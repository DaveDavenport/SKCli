CXXFLAGS+=-std=c++11

SOURCES=$(wildcard *.cc *.hpp)
OUTPUT=stkcli

OBJECTS=$(SOURCES:%.cc=%.o)


all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CXX) -o $@ $^  $(CXXFLAGS) $(CXXLIBS)
