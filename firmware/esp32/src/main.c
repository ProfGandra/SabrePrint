// Sabre 3D - diagnostico inicial ESP32-S3 CAM N16R8
// Nenhum GPIO de camera/SD e acionado. USB Host nao habilitado.
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_heap_caps.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "nvs_flash.h"
#include "esp_http_server.h"

#define SABRE_SSID "Sabre3D"
#define SABRE_PASS "Sabre3D-Teste26" // SENHA TEMPORARIA: TROCAR ANTES DO USO REAL
#define SABRE_MAX_CLIENTS 4

static const char *TAG = "Sabre3D";
static httpd_handle_t server = NULL;
static const char page[] =
"<!doctype html><html lang='pt-BR'><head><meta charset='utf-8'>"
"<meta name='viewport' content='width=device-width,initial-scale=1'>"
"<title>Sabre 3D - Diagnostico</title>"
"<style>body{background:#0d1420;color:#e8eef8;font:16px system-ui;margin:0;padding:24px}"
"main{max-width:680px;margin:auto}.card{background:#172233;border:1px solid #33475d;"
"padding:20px;border-radius:14px}h1{color:#78dfc8}pre{white-space:pre-wrap;overflow-wrap:anywhere}"
"small{color:#9daec3}</style></head><body><main><div class='card'>"
"<h1>Sabre 3D - Diagnostico</h1><p>ESP32-S3 conectado ao Wi-Fi local.</p>"
"<p><strong>Sem controle de impressora.</strong> USB Host, camera e microSD ainda nao testados.</p>"
"<pre id='data'>Consultando...</pre><small>Desenvolvido por DGandra - 2026</small>"
"</div></main><script>async function load(){try{let r=await fetch('/api/diagnostico',{cache:'no-store'});"
"document.getElementById('data').textContent=JSON.stringify(await r.json(),null,2)}"
"catch(e){document.getElementById('data').textContent='Erro: '+e}}"
"load();setInterval(load,5000)</script></body></html>";

static esp_err_t page_handler(httpd_req_t *req) {
    httpd_resp_set_type(req, "text/html; charset=utf-8");
    return httpd_resp_send(req, page, HTTPD_RESP_USE_STRLEN);
}

static esp_err_t status_handler(httpd_req_t *req) {
    esp_chip_info_t chip;
    esp_chip_info(&chip);
    uint32_t flash_bytes = 0;
    esp_err_t flash_result = esp_flash_get_size(NULL, &flash_bytes);
    size_t psram_total = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
    size_t psram_free = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    char json[640];
    int n = snprintf(json, sizeof(json),
        "{\"projeto\":\"Sabre 3D\",\"modo\":\"diagnostico\","
        "\"nucleos\":%d,\"revisao_chip\":%d,"
        "\"flash_bytes\":%" PRIu32 ",\"flash_detectada\":%s,"
        "\"psram_total_bytes\":%u,\"psram_livre_bytes\":%u,"
        "\"heap_livre_bytes\":%u,\"wifi_ssid\":\"%s\","
        "\"microSD\":\"nao testado\",\"usb_host\":\"nao testado\","
        "\"camera\":\"nao testada\"}",
        chip.cores, chip.revision, flash_bytes,
        flash_result == ESP_OK ? "true" : "false",
        (unsigned)psram_total, (unsigned)psram_free,
        (unsigned)esp_get_free_heap_size(), SABRE_SSID);
    if (n < 0 || n >= sizeof(json)) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Erro de diagnostico");
        return ESP_FAIL;
    }
    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_hdr(req, "Cache-Control", "no-store");
    return httpd_resp_send(req, json, HTTPD_RESP_USE_STRLEN);
}

static void start_http(void) {
    httpd_config_t cfg = HTTPD_DEFAULT_CONFIG();
    cfg.max_uri_handlers = 4;
    ESP_ERROR_CHECK(httpd_start(&server, &cfg));
    httpd_uri_t root = {.uri = "/", .method = HTTP_GET, .handler = page_handler};
    httpd_uri_t api = {.uri = "/api/diagnostico", .method = HTTP_GET, .handler = status_handler};
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &root));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &api));
}

static void start_ap(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *ap = esp_netif_create_default_wifi_ap();
    ESP_ERROR_CHECK(ap ? ESP_OK : ESP_FAIL);
    wifi_init_config_t init = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&init));
    wifi_config_t cfg = {0};
    memcpy(cfg.ap.ssid, SABRE_SSID, sizeof(SABRE_SSID));
    cfg.ap.ssid_len = strlen(SABRE_SSID);
    memcpy(cfg.ap.password, SABRE_PASS, sizeof(SABRE_PASS));
    cfg.ap.channel = 1;
    cfg.ap.max_connection = SABRE_MAX_CLIENTS;
    cfg.ap.authmode = WIFI_AUTH_WPA2_PSK;
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &cfg));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "Wi-Fi AP: %s | URL: http://192.168.4.1", SABRE_SSID);
}

void app_main(void) {
    esp_err_t nvs = nvs_flash_init();
    if (nvs == ESP_ERR_NVS_NO_FREE_PAGES || nvs == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvs = nvs_flash_init();
    }
    ESP_ERROR_CHECK(nvs);
    esp_chip_info_t chip;
    esp_chip_info(&chip);
    uint32_t flash = 0;
    ESP_ERROR_CHECK(esp_flash_get_size(NULL, &flash));
    ESP_LOGI(TAG, "ESP32-S3: %d nucleos, revisao %d", chip.cores, chip.revision);
    ESP_LOGI(TAG, "Flash: %" PRIu32 " bytes; PSRAM disponivel: %u bytes",
             flash, (unsigned)heap_caps_get_total_size(MALLOC_CAP_SPIRAM));
    ESP_LOGW(TAG, "Modo diagnostico: SEM comandos G-code, SEM USB Host e SEM camera/SD");
    start_ap();
    start_http();
    while (1) {
        ESP_LOGI(TAG, "Ativo | heap livre: %u bytes",
                 (unsigned)esp_get_free_heap_size());
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
