# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/newlib/include $(PROJECT_PATH)/components/newlib/newlib/include $(PROJECT_PATH)/components/newlib/newlib/port/include
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/newlib $(PROJECT_PATH)/components/newlib/newlib/lib/libc_nano.a $(PROJECT_PATH)/components/newlib/newlib/lib/libm.a -lnewlib
COMPONENT_LINKER_DEPS += $(PROJECT_PATH)/components/newlib/newlib/lib/libc_nano.a $(PROJECT_PATH)/components/newlib/newlib/lib/libm.a
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += newlib
component-newlib-build: 
