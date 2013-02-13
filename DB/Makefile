CXXFLAGS+=-std=c++11 -Wall

SOURCES=$(wildcard *.cc)

LIB_PREFIX=libstk-db
BUILD_DIR_OBJECTS=$(BUILD_DIR)/objects/

OUTPUT=$(BUILD_DIR)$(LIB_PREFIX).a

OBJECTS=$(SOURCES:%.cc=$(BUILD_DIR_OBJECTS)$(LIB_PREFIX)%.o)


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

-include $(DEPEND_FILES)

$(BUILD_DIR_OBJECTS)$(LIB_PREFIX)%.o: %.cc
	$(info Compiling: $< -> $@)	
	@ $(CXX) $(CXXFLAGS) -o $@ -c $<

$(OUTPUT): $(OBJECTS)
	$(info Linking: $@)
	@$(AR) rcs $@ $^ 

clean:
	@rm -rf $(OBJECTS) $(OUTPUT) .depend

