/*
* SmartHome.h
*
* Created: 4/1/2024 3:06:35 AM
*  Author: NOTEBOOK
*/


#ifndef SMARTHOME_H_
#define SMARTHOME_H_

#include "RGB_Cfg.h"
typedef struct {
	u8 str[20];
	void(*ptr)(u16);
}task_t;
typedef enum {
	LED_ON=0,
	LED_OFF,
	RELAY_ON,
	RELAY_OFF,
	LCD,
	SERVO,
	LEDON_ALL,
	LEDOFF_ALL,
	NO_TASK
}task_num_t;
typedef enum {
	CONTROL_MODE,
	RGB_MODE
}tasks_mode_t;
typedef struct {
	u8 str[10];
	RGB_COLOR_NAMES_t rgb_color;
	}rgb_samrt_t;

void smart_home_init(void);
u16 string_ins_info(u8 *str,u8 *str_ins);
void led_on(u8 led_num);
void led_off(u8 led_num);
void led_on_all(void);
void led_off_all(void);
void relay_on(u8 r_num);
void relay_off(u8 r_num);
void lcd_display(u16 num);
void servo_move(u8 angle);
u8 compare_str(u8 *str1,u8 *str2);
task_num_t task_search(u8 *str_ins);
u8 RGB_search(u8 *str_ins);
void smart_home_runnable(void);
#endif /* SMARTHOME_H_ */