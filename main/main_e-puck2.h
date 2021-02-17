/*

File    : main_e-puck2.h
Author  : Stefano Morgani
Date    : 19 May 2020
REV 1.0

Firmware to be run on the ESP32 of the e-puck2
*/

#ifndef MAIN_E_PUCK_2_H
#define MAIN_E_PUCK_2_H

//////////////////////////////////////////RGB_LED DEFINITIONS//////////////////////////////////////////////
#define RGB_LED2_RED_GPIO		32
#define RGB_LED2_GREEN_GPIO		33
#define RGB_LED2_BLUE_GPIO		25

#define RGB_LED4_RED_GPIO		14
#define RGB_LED4_GREEN_GPIO		27
#define RGB_LED4_BLUE_GPIO		26

#define RGB_LED6_RED_GPIO		22
#define RGB_LED6_GREEN_GPIO		21
#define RGB_LED6_BLUE_GPIO		13

#define RGB_LED8_RED_GPIO		4
#define RGB_LED8_GREEN_GPIO		16
#define RGB_LED8_BLUE_GPIO		15


///////////////////////////////////////////BUTTON DEFINITIONS//////////////////////////////////////////////
#define BUTTON_GPIO		GPIO_NUM_35


#endif /* MAIN_E_PUCK_2_H */