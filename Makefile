MAKEFLAGS=--no-print-directory

CXXFLAGS+=-std=c++11 -Wall

SOURCES=$(wildcard *.cc)


BUILD_DIR=build/
BUILD_DIR_OBJECTS=$(BUILD_DIR)objects/

OBJECTS=$(SOURCES:%.cc=$(BUILD_DIR_OBJECTS)%.o)
OUTPUT=$(BUILD_DIR)stkcli

all: $(OUTPUT)

NODEPS:=clean


##
# Include headers directory
##
CXXFLAGS+=-IHeaders/

CXXLIBS+=-L$(BUILD_DIR) -lstk-db


##
# Database
##
.PHONY: $(BUILD_DIR)/libstk-db.a
DB: $(BUILD_DIR)/libstk-db.a
	$(info Checking: libstk-db.a)
	@$(MAKE) -C DB/ BUILD_DIR="../$(BUILD_DIR)"

.PHONY: doc
doc:
	$(info Checking: documentation)
	@$(MAKE) -C Doc/ BUILD_DIR="../$(BUILD_DIR)"


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

#Don't create dependencies when we're cleaning, for instance
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
    #Chances are, these files don't exist.  GMake will create them and
    #clean up automatically afterwards
    -include $(DEPEND_FILES)
endif

##
# Compiling
##
$(BUILD_DIR_OBJECTS)%.o: %.cc
	$(info Compiling: $< -> $@)	
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<

$(OUTPUT): $(OBJECTS) DB
	$(info Linking: $@)
	@$(CXX) -o $@ $(OBJECTS)  $(CXXFLAGS) $(CXXLIBS)

clean:
	$(info Cleaning...)
	@$(MAKE) -C DB/ clean BUILD_DIR="../$(BUILD_DIR)"
	@$(MAKE) -C Doc/ clean BUILD_DIR="../$(BUILD_DIR)"
	@rm -rf $(OBJECTS) $(OUTPUT) $(DEPEND_FILES) $(BUILD_DIR)

