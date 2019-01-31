# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/lwip/include $(PROJECT_PATH)/components/lwip/include/lwip/apps $(PROJECT_PATH)/components/lwip/include/lwip $(PROJECT_PATH)/components/lwip/lwip/src/include $(PROJECT_PATH)/components/lwip/lwip/src/include/posix $(PROJECT_PATH)/components/lwip/port/esp8266/include $(PROJECT_PATH)/components/lwip/port/esp8266/include/port
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/lwip -llwip
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += lwip
component-lwip-build: 
