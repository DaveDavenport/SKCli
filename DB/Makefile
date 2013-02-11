CXXFLAGS+=-std=c++11 -Wall

SOURCES=$(wildcard *.cc)
OUTPUT=libstk-db.a

OBJECTS=$(SOURCES:%.cc=%.o)


all: $(OUTPUT)


CXXFLAGS+=-I../Headers/


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
	@$(AR) rcs $@ $^ 

clean:
	@rm -rf $(OBJECTS) $(OUTPUT) .depend
