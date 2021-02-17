/*

File    : uart_e-puck2.h
Author  : Stefano Morgani
Date    : 10 January 2018
REV 1.0

Functions to configure and use the UART communication between the ESP32 and both the main processor (F407) and the programmer (F413).
*/

#ifndef UART_E_PUCK_2_H
#define UART_E_PUCK_2_H

#define UART_TX_BUFF_SIZE 22
#define UART_RX_BUFF_SIZE 104
#define RESPONSE_SIZE 103

#define ECHO_TASK_STACK_SIZE	1024
#define ECHO_TASK_PRIO			10

typedef enum {
	SENSORS_BUFF_EMPTY,
	SENSORS_BUFF_FILLED
} sensors_buffer_state_t;

typedef struct {
	sensors_buffer_state_t state;
	uint8_t* data;
} sensors_buffer_t;

/**
 * @brief Task used to exchange data with the F407 through UART (based on asercom protocol).
 *
 * @param *pvParameter	parameter from the xCreateTask 	
 */
void advsercom_task(void *pvParameter);

/**
 * @brief 	UART initialization.
 *
 */
void uart_init(void);

/**
 * @brief Set the buffer content that will be sent to the F407 the next time.
 */
void uart_set_actuators_state(uint8_t *buff);

/**
 * @brief Return the pointer to the most recent UART data received from the F407.
 */
sensors_buffer_t *uart_get_data_ptr(void);

/**
 * @brief Turn on robot body LED.
 */
void turn_on_body_led(void);

/**
 * @brief Turn off robot body LED.
 */
void turn_off_body_led(void);

/**
 * @brief Turn on robot front LED.
 */
void turn_on_front_led(void);

/**
 * @brief Turn off robot front LED.
 */
void turn_off_front_led(void);

/**
 * @brief Return the current selector position.
 * @return selector position between 0 and 15.
 */
uint8_t get_selector(void);

/**
 * @brief Turn on robot LED1 (front side).
 */
void turn_on_led1(void);

/**
 * @brief Turn off robot LED1 (front side).
 */
void turn_off_led1(void);

/**
 * @brief Turn on robot LED3 (right side).
 */
void turn_on_led3(void);

/**
 * @brief Turn off robot LED3 (right side).
 */
void turn_off_led3(void);

/**
 * @brief Set the robot forward/backward speed.
 * @param speed 	speed for both motors between -1000 and 1000.			
 */
void set_speed(int16_t speed);

/**
 * @brief Enable obstacle avoidance behavior on the robot.
 */
void enable_obstacle_avoidance(void);

/**
 * @brief Set the robot pivot rotation speed.
 * @param speed 	if speed is positive then right rotation, otherwise left rotation.
 */
void set_pivot_turn_speed(int16_t speed);

#endif /* UART_E_PUCK_2_H */