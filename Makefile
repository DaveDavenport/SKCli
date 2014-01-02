EMPTY=

# Check for clang.
CLANGXX=$(shell which clang++)
ifneq ($(CLANGXX),$(EMPTY))
CXX=$(CLANGXX)
endif
PKG_CONFIG=$(shell which pkg-config)
ifeq ($(PKG_CONFIG),$(EMPTY))
$(error pkg-config not found.)
endif

PKG_CONFIG_VERSION=$(shell $(PKG_CONFIG) --silence-errors --modversion sqlite3)

ifeq ($(PKG_CONFIG_VERSION),$(EMPTY))
$(error sqlite3 not found) 
endif

PREFIX?=$(HOME)/.local/
CXXFLAGS+=-std=c++11 -Wall -Wall -Wextra -g3 -Wno-unused-parameter


MAKEFLAGS=--no-print-directory



SOURCE_DIR=Source
SOURCES=$(wildcard $(SOURCE_DIR)/*.cc)
BUILD_DIR=build/
BUILD_DIR_OBJECTS=$(BUILD_DIR)objects/

OBJECTS=$(SOURCES:%.cc=$(BUILD_DIR_OBJECTS)%.o)
OUTPUT=$(BUILD_DIR)stkcli

all: $(OUTPUT)

NODEPS:=clean doc


##
# Include headers directory
##
CXXFLAGS+=-IHeaders/

CXXLIBS+=-L$(BUILD_DIR) -lstk-db $(shell $(PKG_CONFIG) --libs sqlite3)


##
# Database
##
.PHONY: $(BUILD_DIR)/libstk-db.a
DB: $(BUILD_DIR)/libstk-db.a
	$(info Checking: libstk-db.a)
	@$(MAKE) -C DB/ BUILD_DIR="../$(BUILD_DIR)" CXX=$(CXX) CXXFLAG="$(CXXFLAGS)"

.PHONY: doc
doc:
	$(info Checking: documentation)
	@$(MAKE) -C Doc/ BUILD_DIR="../$(BUILD_DIR)"


$(BUILD_DIR):
	$(info Create build directory)
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR_OBJECTS):
	$(info Create build object directory)
	@mkdir -p $(BUILD_DIR_OBJECTS)/$(SOURCE_DIR)

##
# Header tracking.
##
DEPEND_FILES=$(OBJECTS:%.o=%.d)

$(BUILD_DIR_OBJECTS)%.d: %.cc $(BUILD_DIR) $(BUILD_DIR_OBJECTS) 
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
	@$(MAKE) -C DB/ clean BUILD_DIR="../$(BUILD_DIR)" CXX=$(CXX)
	@$(MAKE) -C Doc/ clean BUILD_DIR="../$(BUILD_DIR)" CXX=$(CXX)
	@rm -rf $(OBJECTS) $(OUTPUT) $(DEPEND_FILES) $(BUILD_DIR)
	@find . -iname *.orig -delete

##
# Installing
##
install: $(OUTPUT)
	$(info Installing $(notdir $(OUTPUT)) to $(PREFIX))
	@install $(OUTPUT) $(PREFIX)/bin/


##
# Indenting
##
indent:
	@astyle -R --style=linux -S -C -D -N -H -L -W3 -f *.cc *.hpp
