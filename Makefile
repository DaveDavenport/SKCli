MAKEFLAGS=--no-print-directory

CXXFLAGS+=-std=c++11 -Wall

SOURCES=$(wildcard *.cc)
OUTPUT=stkcli

OBJECTS=$(SOURCES:%.cc=$(BUILD_DIR)%.o)

BUILD_DIR=build/

all: $(BUILD_DIR)$(OUTPUT)


##
# Include headers directory
##
CXXFLAGS+=-IHeaders/

CXXLIBS+=-LDB/ -lstk-db


##
# Database
##
.PHONY: DB
DB:
	$(MAKE) -C DB/

.PHONY: doc
doc:
	$(MAKE) -C Doc/


build:
	$(info Create build directory)
	@mkdir -p $(BUILD_DIR)

##
# Header tracking.
##
DEPEND_FILES=$(OBJECTS:%.o=%.d)

$(BUILD_DIR)%.d: %.cc  build
	$(info Finding dependencies: $<)
	@$(CXX) $(CXXFLAGS) -MM -MF $@ -MT $(@:%.d=%.o)  $<

-include $(DEPEND_FILES)

##
# Compiling
##
$(BUILD_DIR)%.o: %.cc
	$(info Compiling: $< -> $@)	
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILD_DIR)$(OUTPUT): $(OBJECTS) DB
	$(info Linking: $@)
	@$(CXX) -o $@ $(OBJECTS)  $(CXXFLAGS) $(CXXLIBS)

clean:
	$(MAKE) -C DB/ clean
	$(MAKE) -C Doc/ clean
	@rm -rf $(OBJECTS) $(OUTPUT) $(DEPEND_FILES) $(BUILD_DIR)



