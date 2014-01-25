EMPTY=
PKG_CONFIG=$(shell which pkg-config)
ifeq ($(PKG_CONFIG),$(EMPTY))
$(error pkg-config not found.)
endif



CXXFLAGS+=-std=c++11 -Wall 

SOURCES=$(wildcard *.cc)

LIB_PREFIX=libstk-db
BUILD_DIR_OBJECTS=$(BUILD_DIR)/objects/

OUTPUT=$(BUILD_DIR)$(LIB_PREFIX).a

OBJECTS=$(SOURCES:%.cc=$(BUILD_DIR_OBJECTS)$(LIB_PREFIX)%.o)

NODEPS:=clean

all: $(OUTPUT)


CXXFLAGS+=-I../Headers/


##
# Header tracking.
##
DEPEND_FILES=$(OBJECTS:%.o=%.d)

$(BUILD_DIR_OBJECTS):
	@mkdir -p $@

$(BUILD_DIR_OBJECTS)$(LIB_PREFIX)%.d: %.cc $(BUILD_DIR_OBJECTS)
	$(info Finding dependencies: $<)
	@$(CXX) $(CXXFLAGS) -MM -MF $@ -MT $(@:%.d=%.o)  $<

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
    #Chances are, these files don't exist.  GMake will create them and
    #clean up automatically afterwards
-include $(DEPEND_FILES)
endif

$(BUILD_DIR_OBJECTS)$(LIB_PREFIX)%.o: %.cc
	$(info Compiling: $< -> $@)	
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<

$(OUTPUT): $(OBJECTS)
	$(info Linking: $@)
	@$(AR) rcs $@ $^ 
clean:
	@rm -rf $(OBJECTS) $(OUTPUT) .depend

