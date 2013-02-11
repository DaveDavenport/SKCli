CXXFLAGS+=-std=c++11 -Wall

SOURCES=$(wildcard *.cc)
OUTPUT=stkcli

OBJECTS=$(SOURCES:%.cc=%.o)


all: $(OUTPUT)


##
# Include headers directory
##
CXXFLAGS+=-IHeaders/

CXXLIBS+=-LDB/ -lstk-db


# Database
.PHONY: DB
DB:
	$(MAKE) -C DB/



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

$(OUTPUT): $(OBJECTS) DB
	$(info Linking: $@)
	@$(CXX) -o $@ $(OBJECTS)  $(CXXFLAGS) $(CXXLIBS)

clean:
	$(MAKE) -C DB/ clean
	@rm -rf $(OBJECTS) $(OUTPUT) .depend
