#include "StdTypes.h"
#include "UART_Service.h"
#include "DIO_Int.h"
#include "SmartHome.h"
#include "LCD_Int.h"
#include "RGB_Int.h"
#include "SmartHome_Cfg.h"
u8 str_ins[10];
extern DIO_Pin_t leds_arr[leds_num];
task_t tasks[8]={{"ledon",led_on},
                 {"ledoff",led_off},
                 {"relayon",relay_on},
                 {"relayoff",relay_off},
                 {"lcd",lcd_display},
                 {"servo",servo_move},
				 {"ledonall",led_on_all},
				 {"ledoffall",led_off_all} 
				  };
rgb_samrt_t rgb_scolor[15]={
	{"red",RED},
	{"green",GREEN},
	{"white",WHITE},
	{"purpel",PURPEL},
	{"blue",BLUE},
	{"lightblue",LIGHT_BLUE},
	{"orange",ORANGE},
	{"pink",PINK},
	{"lightorange",LIGHT_ORANGE},
	{"darkpurpel",DARK_PURPEL},
	{"muv",MUV},
	{"yellow",YELLOW},
	{"ment",MENT},
	{"semon",SEMON},
	{"lime",LIME}
};
u16 string_ins_info(u8 *str,u8 *str_ins){
	//UART_ReceiveString(str);
	u8 i,j=0,f=0;
	  u16 num=0;
	for(i=0;str[i];i++){
		if(str[i]=='_'){
			j=i;
			f=1;
			
		}
		else{
			if(f==1){
				num=num*10+str[i]-'0';
			}
			else{
				str_ins[i]=str[i];
			}
			
		}
		
	}
	if(f==1){
		str_ins[j]=0;
	}
	else{
		str_ins[i]=0;
	}
	
	return num;
}
u8 compare_str(u8 *str1,u8 *str2){
	u8 i;

	for(i=0;str1[i]||str2[i];i++){

		if(str1[i]!=str2[i]){
			return 0;
		}

	}
	return 1;
}
task_num_t task_search(u8 *str_ins){
	task_num_t task_num=NO_TASK;
	u8 i;
	for(i=0;i<8;i++){
		if(compare_str(tasks[i].str,str_ins)){
	task_num=i;
		}
		
	}
	return task_num;
}
u8 RGB_search(u8 *str_ins){
	u8 rgb_return;
	u8 i;
	for(i=0;i<15;i++){
		if(compare_str(rgb_scolor[i].str,str_ins)){
			return rgb_scolor[i].rgb_color;
		}	
	}
return 255;
}
void led_on(u8 led_num){
	DIO_WritePin(leds_arr[led_num-1],HIGH);
}
void led_off(u8 led_num){
	DIO_WritePin(leds_arr[led_num-1],LOW);
}
void led_on_all(void){
	for(u8 i=0;i<leds_num;i++){
		DIO_WritePin(leds_arr[i],HIGH);
	}
}
void led_off_all(void){
	for(u8 i=0;i<leds_num;i++){
		DIO_WritePin(leds_arr[i],LOW);
	}
}
void relay_on(u8 r_num){
	if(r_num==1){
		DIO_WritePin(relay1_pin,HIGH);
	}
	if(r_num==2){
		DIO_WritePin(relay2_pin,HIGH);
	}
}
void relay_off(u8 r_num){
	if(r_num==1){
		DIO_WritePin(relay1_pin,LOW);
	}
	if(r_num==2){
		DIO_WritePin(relay2_pin,LOW);
	}
}
void lcd_display(u16 num){
	LCD_SetCursor(2,1);
	LCD_WriteString("lcd: ");
	LCD_WriteNumber(num);
	LCD_WriteString("                  ");
}
void servo_move(u8 angle){
	
}
void smart_home_init(void){
	RGB_init();
}
void smart_home_runnable(void){
	u8 task,i=0;
	static u8 flag;
	u16 num,rgb_retun;
	u8 str[10];
	UART_ReceiveString(str);
	num=string_ins_info(str,str_ins);
	
	
	//task=task_search(str_ins);
	//tasks[task].ptr(num);
	
	LCD_SetCursor(1,1);
	LCD_WriteString(str_ins);
	LCD_WriteString("                    ");
	
	task=task_search(str_ins);
	if(task==NO_TASK){
		
	}
	else{
		tasks[task].ptr(num);
	}
	
	rgb_retun=RGB_search(str_ins);
	if(rgb_retun!=255){
		RGB_Color(rgb_retun);
	}
	else{
		
	}
	
/*	if(compare_str(str_ins,"RGB")){
		flag=RGB_MODE;
		DIO_TogglePin(PINC0);
	}
	 if (compare_str(str_ins,"CONTROL")){
		flag=CONTROL_MODE;
		DIO_TogglePin(PINC1);
	}
	if(flag==CONTROL_MODE){
		task=task_search(str_ins);
		tasks[task].ptr(num);
	}
	 if(flag==RGB_MODE){

		rgb_retun=RGB_search(str_ins);
		RGB_Color(rgb_retun);
	}*/
	
	
	
}