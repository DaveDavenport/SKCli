CXXFLAGS+=-std=c++11 -Wall

SOURCES=$(wildcard *.cc)
OUTPUT=stkcli

OBJECTS=$(SOURCES:%.cc=%.o)


all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CXX) -o $@ $^  $(CXXFLAGS) $(CXXLIBS)


clean:
	rm -rf $(OBJECTS)
