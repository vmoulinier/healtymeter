# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/ssl/include $(PROJECT_PATH)/components/ssl/mbedtls/mbedtls/include $(PROJECT_PATH)/components/ssl/mbedtls/port/esp8266/include $(PROJECT_PATH)/components/ssl/mbedtls/port/openssl/include
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/ssl -lssl
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += ssl
component-ssl-build: 
