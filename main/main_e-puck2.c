/*
 
 File    : main_e-puck2.c
 Author  : Eiji NII
 Date    : 19 May 2020
 REV 1.0
 
 Firmware to be run on the ESP32 of the e-puck2
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/xtensa_api.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_attr.h"   
#include "esp_err.h"
#include "main_e-puck2.h"
#include "rgb_led_e-puck2.h"
#include "button_e-puck2.h"
#include "uart_e-puck2.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_timer.h"

#define PRINT_TAG  "GC-DEMO"

void imu_task(void *pvParameter) {
    float angle_deg = 0.0;
    float gyro_z_dps = 0.0;
    int16_t gyro_z;
    sensors_buffer_t *sensor_buff;
    int64_t start, end;
    float time_interval_us;
	int32_t offset_sum = 0;
	uint8_t num_samples = 0;
	int16_t gyro_z_offset = 0;
	uint8_t imu_task_state = 0;
	
	while(1) {
	
		switch(imu_task_state) {
			case 0: // Calibrate Z axis
				sensor_buff = uart_get_data_ptr();
				gyro_z = sensor_buff->data[22] + sensor_buff->data[23]*256;
				offset_sum += gyro_z;
				num_samples++;
				if(num_samples == 64) {
					gyro_z_offset = offset_sum>>6;
					ESP_LOGI(PRINT_TAG, "offset=%d", gyro_z_offset);
					imu_task_state = 2;
				}			
				break;
				
			case 1: // Wait 1 second
				turn_on_led1();
				uart_get_data_ptr(); // This is needed to update the robot state.			
				vTaskDelay(1000/portTICK_PERIOD_MS);
				turn_off_led1();
				uart_get_data_ptr(); // This is needed to update the robot state.
				imu_task_state = 2;
				break;
				
			case 2: // Turn
				set_pivot_turn_speed(150);
				start = esp_timer_get_time();
				imu_task_state = 3;
				break;
			
			case 3: // Rotate 180 degrees
				sensor_buff = uart_get_data_ptr();
				gyro_z = sensor_buff->data[22] + sensor_buff->data[23]*256;
				//ESP_LOGI(DP3T_TAG, "z=%d", gyro_z);
				gyro_z -= gyro_z_offset;
				gyro_z_dps = (float)gyro_z*250.0/32768.0;				
				//ESP_LOGI(DP3T_TAG, "dps=%f", gyro_z_dps);
				end = esp_timer_get_time();
				time_interval_us = end - start;
				start = esp_timer_get_time();
				angle_deg += gyro_z_dps*time_interval_us/1000000.0;
				//ESP_LOGI(DP3T_TAG, "angle=%f", angle_deg);				
				if(angle_deg <= -180.0) {
					angle_deg = 0.0;
					set_speed(0);
					imu_task_state = 1;
				}			
				break;
		}
	}
}
	
void app_main(void) {

    rgb_init();
	button_init();
    uart_init();
    
	vTaskDelay(100/portTICK_PERIOD_MS);		
	xTaskCreatePinnedToCore(imu_task, "imu_task", 2048, NULL, 4, NULL, 1);      
	
    while(1){
		vTaskDelay(250/portTICK_PERIOD_MS);
    }
     
}
