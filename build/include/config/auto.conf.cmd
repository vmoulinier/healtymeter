deps_config := \
	/home/vagrant/healtymeter/components/app_update/Kconfig \
	/home/vagrant/healtymeter/components/aws_iot/Kconfig \
	/home/vagrant/healtymeter/components/esp8266/Kconfig \
	/home/vagrant/healtymeter/components/freertos/Kconfig \
	/home/vagrant/healtymeter/components/libsodium/Kconfig \
	/home/vagrant/healtymeter/components/log/Kconfig \
	/home/vagrant/healtymeter/components/lwip/Kconfig \
	/home/vagrant/healtymeter/components/mdns/Kconfig \
	/home/vagrant/healtymeter/components/mqtt/Kconfig \
	/home/vagrant/healtymeter/components/newlib/Kconfig \
	/home/vagrant/healtymeter/components/pthread/Kconfig \
	/home/vagrant/healtymeter/components/ssl/Kconfig \
	/home/vagrant/healtymeter/components/tcpip_adapter/Kconfig \
	/home/vagrant/healtymeter/components/wpa_supplicant/Kconfig \
	/home/vagrant/healtymeter/components/bootloader/Kconfig.projbuild \
	/home/vagrant/healtymeter/components/esptool_py/Kconfig.projbuild \
	/home/vagrant/healtymeter/components/partition_table/Kconfig.projbuild \
	/home/vagrant/esp-rt/ESP8266_RTOS_SDK/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
