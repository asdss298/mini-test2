#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_heap_caps.h"
#include "esp_chip_info.h"

void app_main(void)
{
    printf("================================\n");
    printf("ESP32-S3 Minimal Test Program\n");
    printf("================================\n");
    
    // 获取芯片信息
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    
    printf("Chip: ESP32-S3 Rev %d\n", chip_info.revision);
    printf("CPU cores: %d\n", chip_info.cores);
    printf("Features: 0x%08X\n", chip_info.features);
    
    // 获取内存信息
    size_t free_heap = esp_get_free_heap_size();
    size_t min_free_heap = esp_get_minimum_free_heap_size();
    
    printf("Free heap: %zu bytes\n", free_heap);
    printf("Min free heap: %zu bytes\n", min_free_heap);
    
    // 检查SPRAM
    #ifdef CONFIG_SPIRAM_SUPPORT
    printf("SPRAM enabled: YES\n");
    size_t spiram_total = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
    size_t spiram_free = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
    printf("SPRAM total: %zu bytes\n", spiram_total);
    printf("SPRAM free: %zu bytes\n", spiram_free);
    #else
    printf("SPRAM enabled: NO\n");
    #endif
    
    printf("\nSystem started successfully!\n");
    
    int count = 0;
    while (1) {
        printf("Loop %d: Free heap = %zu bytes\n", 
               ++count, 
               esp_get_free_heap_size());
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}