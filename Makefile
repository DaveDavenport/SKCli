MAKEFLAGS=--no-print-directory

CXXFLAGS+=-std=c++11 -Wall

SOURCES=$(wildcard *.cc)
OUTPUT=stkcli


BUILD_DIR=build/
BUILD_DIR_OBJECTS=$(BUILD_DIR)objects/

OBJECTS=$(SOURCES:%.cc=$(BUILD_DIR_OBJECTS)%.o)

all: $(BUILD_DIR)$(OUTPUT)


##
# Include headers directory
##
CXXFLAGS+=-IHeaders/

CXXLIBS+=-L$(BUILD_DIR) -lstk-db


##
# Database
##
.PHONY: DB
DB:
	$(MAKE) -C DB/ BUILD_DIR="../$(BUILD_DIR)"

.PHONY: doc
doc:
	$(MAKE) -C Doc/ BUILD_DIR="../$(BUILD_DIR)"


build:
	$(info Create build directory)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR_OBJECTS)

##
# Header tracking.
##
DEPEND_FILES=$(OBJECTS:%.o=%.d)

$(BUILD_DIR_OBJECTS)%.d: %.cc  build
	$(info Finding dependencies: $<)
	@$(CXX) $(CXXFLAGS) -MM -MF $@ -MT $(@:%.d=%.o)  $<

-include $(DEPEND_FILES)

##
# Compiling
##
$(BUILD_DIR_OBJECTS)%.o: %.cc
	$(info Compiling: $< -> $@)	
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<

$(BUILD_DIR)$(OUTPUT): $(OBJECTS) DB
	$(info Linking: $@)
	@$(CXX) -o $@ $(OBJECTS)  $(CXXFLAGS) $(CXXLIBS)

clean:
	$(MAKE) -C DB/ clean BUILD_DIR="../$(BUILD_DIR)"
	$(MAKE) -C Doc/ clean BUILD_DIR="../$(BUILD_DIR)"
	@rm -rf $(OBJECTS) $(OUTPUT) $(DEPEND_FILES) $(BUILD_DIR)

