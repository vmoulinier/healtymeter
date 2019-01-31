#include <stdio.h>
#include <string.h>

#include "../components/freertos/include/freertos/FreeRTOS.h"
#include "../components/freertos/include/freertos/event_groups.h"
#include "../components/freertos/include/freertos/task.h"
#include "../components/esp8266/include/esp_event_loop.h"
#include "../components/esp8266/include/rom/ets_sys.h"
#include "../components/nvs_flash/include/nvs_flash.h"
#include "../components/esp8266/include/driver/gpio.h"
#include "../components/esp8266/include/esp_system.h"
#include "../components/esp8266/include/driver/pwm.h"
#include "../components/esp8266/include/esp_wifi.h"
#include "../components/log/include/esp_log.h"
#include "../components/freertos/include/freertos/timers.h"

// Pin Definitions
#define LEDB_1_PIN_VIN	            14
#define LEDB_2_PIN_VIN	            12
#define POTENTIOMETER3V3_PIN_SIG	A0
#define PUSHBUTTON_PIN_2	        00
#define TILTSWITCH_PIN_2	        02

/* The examples use simple WiFi configuration that you can set via
   'make menuconfig'.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_ESP_WIFI_MODE_AP   CONFIG_ESP_WIFI_MODE_AP //TRUE:AP FALSE:STA
#define EXAMPLE_ESP_WIFI_SSID      CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS      CONFIG_ESP_WIFI_PASSWORD
#define EXAMPLE_MAX_STA_CONN       CONFIG_MAX_STA_CONN

#define GREEN_LED_PIN GPIO_Pin_14
#define GREEN_LED_NUM GPIO_NUM_14

#define TILT_SENSOR_PIN GPIO_Pin_5
#define TILT_SENSOR_NUM GPIO_NUM_5

TimerHandle_t timer_led;

// /* FreeRTOS event group to signal when we are connected*/
// static EventGroupHandle_t wifi_event_group;

// /* The event group allows multiple bits for each event,
//    but we only care about one event - are we connected
//    to the AP with an IP? */
// const int WIFI_CONNECTED_BIT = BIT0;

// static const char *TAG = "simple wifi";

// static esp_err_t event_handler(void *ctx, system_event_t *event) {
//     switch(event->event_id) {
//     case SYSTEM_EVENT_STA_START:
//         esp_wifi_connect();
//         break;
//     case SYSTEM_EVENT_STA_GOT_IP:
//         ESP_LOGI(TAG, "got ip:%s",
//                  ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
//         xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
//         break;
//     case SYSTEM_EVENT_AP_STACONNECTED:
//         ESP_LOGI(TAG, "station:"MACSTR" join, AID=%d",
//                  MAC2STR(event->event_info.sta_connected.mac),
//                  event->event_info.sta_connected.aid);
//         break;
//     case SYSTEM_EVENT_AP_STADISCONNECTED:
//         ESP_LOGI(TAG, "station:"MACSTR"leave, AID=%d",
//                  MAC2STR(event->event_info.sta_disconnected.mac),
//                  event->event_info.sta_disconnected.aid);
//         break;
//     case SYSTEM_EVENT_STA_DISCONNECTED:
//         esp_wifi_connect();
//         xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
//         break;
//     default:
//         break;
//     }
//     return ESP_OK;
// }

// void wifi_init_softap() {
//     wifi_event_group = xEventGroupCreate();

//     tcpip_adapter_init();
//     ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));
//     wifi_config_t wifi_config = {
//         .ap = {
//             .ssid = EXAMPLE_ESP_WIFI_SSID,
//             .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
//             .password = EXAMPLE_ESP_WIFI_PASS,
//             .max_connection = EXAMPLE_MAX_STA_CONN,
//             .authmode = WIFI_AUTH_WPA_WPA2_PSK
//         },
//     };
//     if (strlen(EXAMPLE_ESP_WIFI_PASS) == 0) {
//         wifi_config.ap.authmode = WIFI_AUTH_OPEN;
//     }

//     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
//     ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
//     ESP_ERROR_CHECK(esp_wifi_start());

//     ESP_LOGI(TAG, "wifi_init_softap finished.SSID:%s password:%s",
//              EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
// }

// void wifi_init_sta() {
//     wifi_event_group = xEventGroupCreate();

//     tcpip_adapter_init();
//     ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL) );

//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));
//     wifi_config_t wifi_config = {
//         .sta = {
//             .ssid = EXAMPLE_ESP_WIFI_SSID,
//             .password = EXAMPLE_ESP_WIFI_PASS
//         },
//     };

//     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
//     ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
//     ESP_ERROR_CHECK(esp_wifi_start() );

//     ESP_LOGI(TAG, "wifi_init_sta finished.");
//     ESP_LOGI(TAG, "connect to ap SSID:%s password:%s",
//              EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
// }

void timer_green_led(TimerHandle_t th) {
    gpio_set_level(GREEN_LED_NUM, 0);
}

void handle_tilt(void *param) {
    gpio_set_level(GREEN_LED_NUM, 1);
    xTimerStartFromISR(timer_led, NULL) ;

    //   int duration = pdMS_TO_TICKS(200) ;
    //     vTaskDelay(duration) ;
    //     
    //     vTaskDelay(duration) ;
    // for(int a=0;a<100;a++) {
    //     vTaskDelay(duration) ;
    //     gpio_set_level(GREEN_LED_NUM, 1);
    //     vTaskDelay(duration) ;
    //     gpio_set_level(GREEN_LED_NUM, 0);
    // }
}

void app_main(void) {

    gpio_config_t c;
    c.mode = GPIO_MODE_OUTPUT;
    c.pin_bit_mask = GREEN_LED_PIN;
    c.intr_type = GPIO_INTR_DISABLE;
    c.pull_down_en = c.pull_up_en = 0;
    gpio_config(&c);

    c.mode = GPIO_MODE_INPUT;
    c.pin_bit_mask = TILT_SENSOR_PIN;
    c.intr_type = GPIO_INTR_POSEDGE;
    c.pull_down_en = c.pull_up_en = 0;
    gpio_config(&c);

    timer_led = xTimerCreate("Timer", pdMS_TO_TICKS(10), pdFALSE, 0, timer_green_led) ;

    gpio_install_isr_service(0) ;
    gpio_isr_handler_add(TILT_SENSOR_NUM, handle_tilt, NULL);

    

    // printf("SDK version:%s\n", esp_get_idf_version());

    // //Initialize NVS
    // esp_err_t ret = nvs_flash_init();
    // if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
    //   ESP_ERROR_CHECK(nvs_flash_erase());
    //   ret = nvs_flash_init();
    // }
    // ESP_ERROR_CHECK(ret);
        
    // #if EXAMPLE_ESP_WIFI_MODE_AP
    //     ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    //     wifi_init_softap();
    // #else
    //     ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    //     wifi_init_sta();
    // #endif /*EXAMPLE_ESP_WIFI_MODE_AP*/
}