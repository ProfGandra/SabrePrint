#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_chip_info.h"

static const char *TAG = "Sabre3D";

void app_main(void)
{
    esp_chip_info_t chip;
    esp_chip_info(&chip);
    ESP_LOGI(TAG, "Sabre 3D - firmware inicial (sem controle de impressora)");
    ESP_LOGI(TAG, "ESP32: %d nucleos; revision %d", chip.cores, chip.revision);
    ESP_LOGW(TAG, "USB Host, microSD, Wi-Fi e G-code ainda nao implementados.");

    while (1) {
        ESP_LOGI(TAG, "Sistema ativo (modo diagnostico)");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
