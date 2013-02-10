CXXFLAGS+=-std=c++11 -Wall

SOURCES=$(wildcard *.cc)
OUTPUT=stkcli

OBJECTS=$(SOURCES:%.cc=%.o)


all: $(OUTPUT)

##
# Header tracking.
##
depend: .depend

.depend: $(SOURCES)
	$(info Calculating dependencies for: $^)
	@rm -f $@
	@$(CXX) -MM $^ > $@ 

-include .depend

%.o: %.cc
	$(info Compiling: $< -> $@)	
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<

$(OUTPUT): $(OBJECTS)
	$(info Linking: $@)
	@$(CXX) -o $@ $^  $(CXXFLAGS) $(CXXLIBS)

clean:
	@rm -rf $(OBJECTS) $(PROGRAM) .depend
