/*
 * clock_func.c
 *
 *  Created on: Jan 3, 2024
 *      Author: KIEN
 */

#include "ILI9225.h"
#include "Humidity.h"
#include "RTC.h"
#include "string.h"
#include "stdio.h"
#include "FLASH.h"
#include "stdlib.h"
#include <DHT11.h>
extern I2C_HandleTypeDef hi2c2;

extern SPI_HandleTypeDef hspi1;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;

volatile uint8_t i = 1;
char str1[20];
char str2[20];
char str3[20];
uint8_t b,b1,rub_screen = 0, main_screen = 0, re_write = 0;

uint8_t alarm_buff[3];
volatile uint32_t counter = 0, time_last_state = 0, time_last_choose = 0, time_last_flag = 0, time_last_intro = 0;
uint16_t count = 0;
uint16_t button1, button = 0;
uint16_t nut = 0;
volatile uint8_t change_time, choose = 0, state = 0, flag = 0;
volatile int32_t temp, result_luu;
uint8_t a=0;
DHT_Name DHT1;
uint8_t temperature[20];
uint8_t humidity[20];

DateTime datetime; // thoi gian hien tai
DateTime alarm;    // thoi gian hen bao thuc
volatile uint8_t check_state = 0, check_choose = 0, check_flag = 0,cnt=0, check_intro =0;

//void delay(uint16_t us)
//{
//    __HAL_TIM_SET_COUNTER(&htim2, 0); // set the counter value a 0
//    while (__HAL_TIM_GET_COUNTER(&htim2) < (us)); // wait for the counter to reach the us input in the parameter
//}


//////cai dat thoi bang xoay encoder
void value_changed(uint8_t *value)
{
    *value = *value + ((int32_t)(htim4.Instance->CNT) - temp) / 4;
    result_luu = *value;
    RTC_WriteTime(&datetime);
    temp = (int32_t)(htim4.Instance->CNT);
}


/// cai dat gio bao thuc
void alarm_changed(uint8_t *value) // xem lại
{
    *value = *value + ((uint8_t)(htim4.Instance->CNT) - temp) / 4;
    result_luu = *value;
    temp = (uint8_t)(htim4.Instance->CNT);
}


void update_change(uint8_t *data_temp, uint8_t data_present, uint8_t data_in,char x_write, char y_write, unsigned int colour_write, char size_write, char x1_rub, char y1_rub, char x2_rub, char y2_rub, unsigned int colour_rub )
{
	char str_number_write[20];
	b1=*data_temp;
    b=data_present = data_in;
    if (*data_temp != data_present)
    {
    	sprintf(str_number_write, "%.2d", data_in);
        fill_rectangle(x1_rub, y1_rub, x2_rub, y2_rub, colour_rub);
        *data_temp = data_present;
        draw_string(x_write, y_write, colour_write, size_write, str_number_write);
    }

}

void update_change_choose(uint8_t *data_temp, uint8_t data_present, uint8_t data_in,char x_write, char y_write, unsigned int colour_write, char size_write, char x1_rub, char y1_rub, char x2_rub, char y2_rub, unsigned int colour_rub )
{

	char str_number_write[20];
	b1=*data_temp;
    b=data_present = data_in;
    sprintf(str_number_write, "%.2d", data_in);
    draw_string(x_write, y_write, colour_write, size_write, str_number_write);
    if (*data_temp != data_present)
    {
        fill_rectangle(x1_rub, y1_rub, x2_rub, y2_rub, colour_rub);
        HAL_Delay(200);
        fill_rectangle(x1_rub, y1_rub, x2_rub, y2_rub, colour_rub);
        HAL_Delay(200);
        *data_temp = data_present;
        draw_string(x_write, y_write, colour_write, size_write, str_number_write);
    }

}


/// ham hien thi khi thay doi thoi gian
//void hien_thi_data(uint8_t data_temp, uint8_t data_present, uint8_t data_in) // state 1 và 3 sao k để 2 state thôi
//{
//    if (state == 1 || state == 3) // thay doi gio
//    {
//        if (choose == 0)
//        {
//            data_present = data_in;
//            if (data_temp != data_present)
//            {
//                fill_rectangle(85, 100, 105, 110, COLOR_WHITE);
//                HAL_Delay(200);
//                fill_rectangle(85, 100, 105, 110, COLOR_WHITE);
//                HAL_Delay(200);
//                data_temp = data_present;
//            }
//        }
//        else if (choose == 1)
//        {
//            data_present = data_in;
//            if (data_temp != data_present)
//            {
//                fill_rectangle(110, 100, 130, 110, COLOR_WHITE);
//                HAL_Delay(200);
//                fill_rectangle(110, 100, 130, 110, COLOR_WHITE);
//                HAL_Delay(200);
//                data_temp = data_present;
//            }
//        }
//        else if (choose == 2)
//        {
//            data_present = data_in;
//            if (data_temp != data_present)
//            {
//                fill_rectangle(140, 100, 160, 110, COLOR_WHITE);
//                HAL_Delay(200);
//                fill_rectangle(140, 100, 160, 110, COLOR_WHITE);
//                HAL_Delay(200);
//                data_present = data_temp;
//            }
//        }
//    }
//    //----------------------------------------------------------------------------------------------
//    else if (state == 2) // thay doi ngay ; có thiếu state 4 không?
//    {
//        if (choose == 0)
//        {
//            data_present = data_in;
//            if (data_temp != data_present)
//            {
//                fill_rectangle(85, 115, 105, 135, COLOR_WHITE);
//                HAL_Delay(200);
//                fill_rectangle(85, 115, 105, 135, COLOR_WHITE);
//                HAL_Delay(200);
//                data_temp = data_present;
//            }
//        }
//        else if (choose == 1)
//        {
//            data_present = data_in;
//            if (data_temp != data_present)
//            {
//                fill_rectangle(110, 115, 130, 135, COLOR_WHITE);
//                HAL_Delay(200);
//                fill_rectangle(110, 115, 130, 135, COLOR_WHITE);
//                HAL_Delay(200);
//                data_temp = data_present;
//            }
//        }
//        else if (choose == 2)
//        {
//            data_present = data_in;
//            if (data_temp != data_present)
//            {
//                fill_rectangle(135, 115, 160, 135, COLOR_WHITE);
//                HAL_Delay(200);
//                fill_rectangle(135, 115, 160, 135, COLOR_WHITE);
//                HAL_Delay(200);
//                data_temp = data_present;
//            }
//        }
//    }
//}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim4.Instance)
	{
		counter = __HAL_TIM_GET_COUNTER(htim);
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) // giải thích hàm callback này
{
    if (GPIO_Pin == GPIO_PIN_4 && HAL_GetTick()- time_last_state > 15)// thay doi state
    {
			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0 )
		{
				check_state = 1;
		}
			time_last_state = HAL_GetTick();
    }
    else if (GPIO_Pin == GPIO_PIN_8 && HAL_GetTick()- time_last_flag > 15)
    {
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == 0)
        {
        	check_flag = 1;

        }
        time_last_flag = HAL_GetTick();
    }
    else if (GPIO_Pin == GPIO_PIN_3 && HAL_GetTick()- time_last_choose > 15)
    {
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0 ) // chon thoi gian can thay doi
        {
        	check_choose = 1;
        }
        time_last_choose = HAL_GetTick();

    }

    else if (GPIO_Pin == GPIO_PIN_2 && HAL_GetTick() - time_last_intro > 15)//bat bang huong dan
    {
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0 )
        {
        	check_intro = 1;
        }
    	time_last_intro = HAL_GetTick();
    }
}


void alarm_buzzer() // coi bao thuc
{
    for (i; i <= 60; i++)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1); // sai thi xem lai set pin
        HAL_Delay(150);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
        HAL_Delay(75);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
        HAL_Delay(200);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
    }
}

void screen_init()
{
    lcd_init();
    fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_BLACK);
    draw_string(30, 60, COLOR_GOLD, 2, "Loading...");
    HAL_Delay(1000);

    fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_WHITE);
    draw_string(50, 50, COLOR_BLUE, 5, "PIF");
    HAL_Delay(100);

    fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_WHITE);
    draw_string(43, 9, COLOR_BLUE, 1, "Pay It Forward");
    draw_line(41, 23, 170, 23, COLOR_BLACK);
    fill_rectangle(0, 25, 220, 55, COLOR_RED);
    HAL_Delay(100);

    draw_string(22, 32, COLOR_GOLD, 1.5, "Temperature:");
    sprintf((char*)temperature, "%.f", DHT1.Temp);
    draw_string(135 , 32, COLOR_GOLD, 1.5, (char*)temperature);
    HAL_Delay(100);


    fill_rectangle(0, 50, 220, 75, COLOR_BLUE);
    HAL_Delay(100);

    draw_string(22, 57, COLOR_GOLD, 1.5, "Humidity:");
    sprintf((char*)humidity, "%.f", DHT1.Humi);
    draw_string(105, 57, COLOR_GOLD, 1.5, (char*)humidity);
    HAL_Delay(100);


    draw_line(5, 171, 215, 171, COLOR_BLACK);
    draw_line(5, 5, 5, 171, COLOR_BLACK);
    // vẽ biểu tượng
    draw_bieu_tuong(2, 27, 0, COLOR_GOLD, 2);
    draw_bieu_tuong(2, 55, 1, COLOR_GOLD, 2);
    draw_bieu_tuong(17, 97, 2, COLOR_DARKBLUE, 2);
    draw_bieu_tuong(17, 117, 3, COLOR_DARKBLUE, 2);
    sprintf(str1, "Time %.2d:%.2d:%.2d", datetime.hour, datetime.min, datetime.second);
    draw_string(40, 100, COLOR_BLACK, 1, str1);
    sprintf(str2, "Date %.2d:%.2d:%.2d", datetime.date, datetime.month, datetime.year);
    draw_string(40, 120, COLOR_BLACK, 1, str2);

}

void re_screen_init()
{
//	lcd_init();
	fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_WHITE);
	HAL_Delay(1000);
    fill_rectangle(0, 25, 220, 55, COLOR_RED);
    HAL_Delay(100);
    draw_string(43, 9, COLOR_BLUE, 1, "Pay It Forward");
    draw_line(41, 23, 170, 23, COLOR_BLACK);
    draw_string(22, 32, COLOR_GOLD, 1.5, "Temperature:");
    sprintf((char*)temperature, "%.f", DHT1.Temp);
    draw_string(135 , 32, COLOR_GOLD, 1.5, (char*)temperature);
    HAL_Delay(100);


    fill_rectangle(0, 50, 220, 75, COLOR_BLUE);
    HAL_Delay(100);

    draw_string(22, 57, COLOR_GOLD, 1.5, "Humidity:");
    sprintf((char*)humidity, "%.f", DHT1.Humi);
    draw_string(105, 57, COLOR_GOLD, 1.5, (char*)humidity);
    HAL_Delay(100);


    draw_line(5, 171, 215, 171, COLOR_BLACK);
    draw_line(5, 5, 5, 171, COLOR_BLACK);
    // vẽ biểu tượng
    draw_bieu_tuong(2, 27, 0, COLOR_GOLD, 2);
    draw_bieu_tuong(2, 55, 1, COLOR_GOLD, 2);
    draw_bieu_tuong(17, 97, 2, COLOR_DARKBLUE, 2);
    draw_bieu_tuong(17, 117, 3, COLOR_DARKBLUE, 2);
    sprintf(str1, "Time %.2d:%.2d:%.2d", datetime.hour, datetime.min, datetime.second);
    draw_string(40, 100, COLOR_BLACK, 1, str1);
    sprintf(str2, "Date %.2d:%.2d:%.2d", datetime.date, datetime.month, datetime.year);
    draw_string(40, 120, COLOR_BLACK, 1, str2);
}


void app_main()
{
    datetime.second = 50;
    datetime.min = 59;
    datetime.hour = 22;
    datetime.day = 8;
    datetime.date = 1;
    datetime.month = 1;
    datetime.year = 24;
    alarm.hour = 0;
    alarm.min = 0;
    RTC_WriteTime(&datetime);

    flash_read(0x801FC00, alarm_buff, 3);// doc hen gio tu FLASH

    HAL_TIM_Encoder_Start_IT(&htim4, TIM_CHANNEL_ALL); // nhay vao ngat doc Encoder

    DHT_Init(&DHT1, DHT11, &htim2, GPIOA, GPIO_PIN_9);

    DHT_ReadTempHum(&DHT1, &a);

    uint8_t second_temp = 0;
    uint8_t second_present = 0;
    uint8_t min_temp = 0;
    uint8_t min_present = 0;
    uint8_t hour_temp = 0;
    uint8_t hour_present = 0;
    uint8_t date_temp = datetime.date;
    uint8_t date_present = 0	;
    uint8_t month_temp = datetime.month;
    uint8_t month_present = 0;
    uint8_t year_temp = datetime.year;
    uint8_t year_present = 0;
    second_temp = datetime.second;
    min_temp = datetime.min;
    hour_temp = datetime.hour;
    uint8_t temperature_temp = DHT1.Temp;
    uint8_t temperature_present = 0;
    float humidity_temp = DHT1.Humi;
    float humidity_present = 0;

    int dd = (int)datetime.date;
    int mm = (int)datetime.month;
    int yy = (int)datetime.year + 2000;
    int julianDay = jdFromDate(dd, mm, yy);
    int timeZone = 7;
    int k = (int)((dd - 2415021) / 29.530588853);
    int lunarDay = getNewMoonDay(k, timeZone);

    screen_init();

	while(1)
	{
			button1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);

	        button = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);

	        nut = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3);

	        if(main_screen == 1)
	        {
	        	re_screen_init();
	        	main_screen = 0;
	        }
	        if(check_state == 1)
	        {
	        	state++;
	        	if (state > 3)	// state = 4 ep ve 0
	        		state = 0;
	        		choose = 0;
					check_state = 0;
	        }

	        if(check_flag == 1)
	        {
				if (flag == 0)
				{
					flag = 1;
					temp = htim4.Instance->CNT;	// luu gia tri ban dau cua encoder
				}
				else if (flag == 1)
				{
					flag = 0;
				}
				else if (flag == 2) // tat buzzer bao thuc
				{
					flag = 0;
					i = 60;
				}
				check_flag = 0;
	        }

	        if(check_choose == 1)
	        {
				if (choose == 0)
				{
					choose = 1;flag = 0; re_write =1;
				}
				else if (choose == 1)
				{
					choose = 2; flag = 0; re_write =1;
				}
				else if (choose == 2)
				{
					choose = 0; flag = 0; re_write =1;
				}
				check_choose = 0;
	        }

	        if(check_intro ==1)
	        {
				if (state == 5)
				{
					state = 0;
					main_screen = 1; // bat ham re_screen_init() chay 1 lan
				}
				else
				{
					state = 5;
					rub_screen = 1;
				}
				check_intro = 0;
	        }
	        if (datetime.hour < 0 || datetime.hour > 23)
	        {
	            datetime.hour = 0;
	            RTC_WriteTime(&datetime);
	        }
	        if (datetime.min < 0 || datetime.min > 59)
	        {
	            datetime.min = 0;
	            RTC_WriteTime(&datetime);
	        }
	        if (datetime.second < 0 || datetime.second > 59)
	        {
	            datetime.second = 0;
	            RTC_WriteTime(&datetime);
	        }
	        if (datetime.date < 0 || datetime.date > 31)
	        {
	            datetime.date = 0;
	            RTC_WriteTime(&datetime);
	        }
	        if (datetime.month < 0 || datetime.month > 12)
	        {
	            datetime.month = 0;
	            RTC_WriteTime(&datetime);
	        }
	        if (datetime.year < 0 || datetime.year > 99)
	        {
	            datetime.year = 0;
	            RTC_WriteTime(&datetime);
	        }

	        if((alarm_buff[0] == datetime.hour) && (alarm_buff[1] == datetime.min) && (flag != 1)){flag=2;alarm_buzzer();}

	        switch (state)
	        {
	        case 0: /// man hinh chinh
	            void man_hinh_chinh()
	            {
	                RTC_ReadTime(&datetime);

	                DHT_ReadTempHum(&DHT1, &a);

	                sprintf((char*)temperature, "%.f", DHT1.Temp);
	                update_change(&temperature_temp, temperature_present, DHT1.Temp, 135 , 32, COLOR_GOLD, 1.5, 135, 27, 155, 45, COLOR_RED);


	                sprintf((char*)humidity, "%.f", DHT1.Humi);
	                update_change(&humidity_temp, humidity_present, DHT1.Humi, 105 , 57, COLOR_GOLD, 1.5, 105, 55, 125, 73, COLOR_BLUE);
                    sprintf(str1, "Time %.2d:%.2d:%.2d", datetime.hour, datetime.min, datetime.second);
	                update_change(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLACK , 1, 140, 100, 160, 110, COLOR_WHITE);

	                update_change(&min_temp, min_present, datetime.min, 110, 100, COLOR_BLACK, 1, 110, 100, 130, 110, COLOR_WHITE);

	                update_change(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLACK, 1, 85, 100, 105, 110, COLOR_WHITE);

	                draw_string(40, 120, COLOR_BLACK, 1, str2);
	                convertSolar2Lunar(dd, mm, yy, timeZone);
	                draw_string(40, 120, COLOR_BLACK, 1, str2);
	                convertSolar2Lunar(dd, mm, yy, timeZone);
	                draw_string(40, 120, COLOR_BLACK, 1, str2);
	                convertSolar2Lunar(dd, mm, yy, timeZone);
	            }
	            man_hinh_chinh();
	            break;

	        case 1: // cai dat gio
	        		RTC_ReadTime(&datetime);
					if (choose == 0)
					{
						if(re_write == 1)
						{
						    update_change(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLACK , 1, 140, 100, 160, 110, COLOR_WHITE);

						    update_change(&min_temp, min_present, datetime.min, 110, 100, COLOR_BLACK, 1, 110, 100, 130, 110, COLOR_WHITE);

						    update_change(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLACK, 1, 85, 100, 105, 110, COLOR_WHITE);

						    update_change(&date_temp, date_present, datetime.date, 85, 120, COLOR_BLACK, 1, 85, 115, 105, 135, COLOR_WHITE);

						    update_change(&month_temp, month_present, datetime.month, 112, 120, COLOR_BLACK, 1, 110, 115, 130, 135, COLOR_WHITE);

						    update_change(&year_temp, year_present, datetime.year, 139, 120, COLOR_BLACK, 1, 135, 115, 160, 135, COLOR_WHITE);

							re_write = 0;
						}
						RTC_ReadTime(&datetime);
		                update_change_choose(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLUEVIOLET, 1, 85, 100, 105, 110, COLOR_WHITE);
						if (flag == 1)
						{
							choose = 0;
							value_changed(&datetime.hour);
			                update_change_choose(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_RED, 1, 85, 100, 105, 110, COLOR_WHITE);

						}
					}
					else if (choose == 1)
					{
						if(re_write == 1)
						{
						    update_change(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLACK , 1, 140, 100, 160, 110, COLOR_WHITE);

						    update_change(&min_temp, min_present, datetime.min, 110, 100, COLOR_BLACK, 1, 110, 100, 130, 110, COLOR_WHITE);

						    update_change(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLACK, 1, 85, 100, 105, 110, COLOR_WHITE);

						    update_change(&date_temp, date_present, datetime.date, 85, 120, COLOR_BLACK, 1, 85, 115, 105, 135, COLOR_WHITE);

						    update_change(&month_temp, month_present, datetime.month, 112, 120, COLOR_BLACK, 1, 110, 115, 130, 135, COLOR_WHITE);

						    update_change(&year_temp, year_present, datetime.year, 139, 120, COLOR_BLACK, 1, 135, 115, 160, 135, COLOR_WHITE);

							re_write = 0;
						}
						RTC_ReadTime(&datetime);
		                update_change_choose(&min_temp, min_present, datetime.min, 111, 100, COLOR_BLUEVIOLET, 1, 110, 100, 130, 110, COLOR_WHITE);
						if (flag == 1)
						{
							choose = 1;
							value_changed(&datetime.min);
			                update_change_choose(&min_temp, min_present, datetime.min, 111, 100, COLOR_RED, 1, 110, 100, 130, 110, COLOR_WHITE);
						}
					}
					else if (choose == 2)
					{
						if(re_write == 1)
						{
						    update_change(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLACK , 1, 140, 100, 160, 110, COLOR_WHITE);

						    update_change(&min_temp, min_present, datetime.min, 110, 100, COLOR_BLACK, 1, 110, 100, 130, 110, COLOR_WHITE);

						    update_change(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLACK, 1, 85, 100, 105, 110, COLOR_WHITE);

						    update_change(&date_temp, date_present, datetime.date, 85, 120, COLOR_BLACK, 1, 85, 115, 105, 135, COLOR_WHITE);

						    update_change(&month_temp, month_present, datetime.month, 112, 120, COLOR_BLACK, 1, 110, 115, 130, 135, COLOR_WHITE);

						    update_change(&year_temp, year_present, datetime.year, 139, 120, COLOR_BLACK, 1, 135, 115, 160, 135, COLOR_WHITE);

							re_write = 0;
						}
						RTC_ReadTime(&datetime);
		                update_change_choose(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLUEVIOLET , 1, 140, 100, 160, 110, COLOR_WHITE);
						if (flag == 1)
						{
							choose = 2;
							value_changed(&datetime.second);
			                update_change_choose(&second_temp, second_present, datetime.second, 140, 100, COLOR_RED , 1, 140, 100, 160, 110, COLOR_WHITE);

						}
					}

	            break;
	            //--------------------------------------------------------------------------------------------------------
	        case 2: // cai dat ngay thang
//				fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_WHITE);
//	        	while(1)
//	        	{
	        		RTC_ReadTime(&datetime);
					if (choose == 0)
					{
						if(re_write == 1)
						{
						    update_change(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLACK , 1, 140, 100, 160, 110, COLOR_WHITE);

						    update_change(&min_temp, min_present, datetime.min, 110, 100, COLOR_BLACK, 1, 110, 100, 130, 110, COLOR_WHITE);

						    update_change(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLACK, 1, 85, 100, 105, 110, COLOR_WHITE);

						    update_change(&date_temp, date_present, datetime.date, 85, 120, COLOR_BLACK, 1, 85, 115, 105, 135, COLOR_WHITE);

						    update_change(&month_temp, month_present, datetime.month, 112, 120, COLOR_BLACK, 1, 110, 115, 130, 135, COLOR_WHITE);

						    update_change(&year_temp, year_present, datetime.year, 139, 120, COLOR_BLACK, 1, 135, 115, 160, 135, COLOR_WHITE);

							re_write = 0;
						}
						RTC_ReadTime(&datetime);
		                update_change_choose(&date_temp, date_present, datetime.date, 85, 120, COLOR_BLUE, 1, 85, 115, 105, 135, COLOR_WHITE);
						if (flag == 1)
						{
							choose = 0;
							value_changed(&datetime.date);
			                update_change_choose(&date_temp, date_present, datetime.date, 85, 120, COLOR_RED, 1, 85, 115, 105, 135, COLOR_WHITE);

						}
					}
					else if (choose == 1)
					{
						if(re_write == 1)
						{
						    update_change(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLACK , 1, 140, 100, 160, 110, COLOR_WHITE);

						    update_change(&min_temp, min_present, datetime.min, 110, 100, COLOR_BLACK, 1, 110, 100, 130, 110, COLOR_WHITE);

						    update_change(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLACK, 1, 85, 100, 105, 110, COLOR_WHITE);

						    update_change(&date_temp, date_present, datetime.date, 85, 120, COLOR_BLACK, 1, 85, 115, 105, 135, COLOR_WHITE);

						    update_change(&month_temp, month_present, datetime.month, 112, 120, COLOR_BLACK, 1, 110, 115, 130, 135, COLOR_WHITE);

						    update_change(&year_temp, year_present, datetime.year, 139, 120, COLOR_BLACK, 1, 135, 115, 160, 135, COLOR_WHITE);

							re_write = 0;
						}
						RTC_ReadTime(&datetime);
		                update_change_choose(&month_temp, month_present, datetime.month, 112, 120, COLOR_BLUE, 1, 110, 115, 130, 135, COLOR_WHITE);
						if (flag == 1)
						{
							choose = 1;
							value_changed(&datetime.month);
			                update_change_choose(&month_temp, month_present, datetime.month, 112, 120, COLOR_RED, 1, 110, 115, 130, 135, COLOR_WHITE);

						}
					}
					else if (choose == 2)
					{
						if(re_write == 1)
						{
						    update_change(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLACK , 1, 140, 100, 160, 110, COLOR_WHITE);

						    update_change(&min_temp, min_present, datetime.min, 110, 100, COLOR_BLACK, 1, 110, 100, 130, 110, COLOR_WHITE);

						    update_change(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLACK, 1, 85, 100, 105, 110, COLOR_WHITE);

						    update_change(&date_temp, date_present, datetime.date, 85, 120, COLOR_BLACK, 1, 85, 115, 105, 135, COLOR_WHITE);

						    update_change(&month_temp, month_present, datetime.month, 112, 120, COLOR_BLACK, 1, 110, 115, 130, 135, COLOR_WHITE);

						    update_change(&year_temp, year_present, datetime.year, 139, 120, COLOR_BLACK, 1, 135, 115, 160, 135, COLOR_WHITE);

							re_write = 0;
						}
						RTC_ReadTime(&datetime);
		                update_change_choose(&year_temp, year_present, datetime.year, 139, 120, COLOR_BLUE, 1, 135, 115, 160, 135, COLOR_WHITE);
						if (flag == 1)
						{
							choose = 2;
							value_changed(&datetime.year);
			                update_change_choose(&year_temp, year_present, datetime.year, 139, 120, COLOR_RED, 1, 135, 115, 160, 135, COLOR_WHITE);
						}
					}
//	        	}
	            break;
	            //-------------------------------------------------------------------------------------------------
	        case 3: // cai dat gio bao thuc
//	        					fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_WHITE);
//
//	        	while(1)
//	        	{
					if (choose == 0)
					{
						if(re_write == 1)
						{
						    update_change(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLACK , 1, 140, 100, 160, 110, COLOR_WHITE);

						    update_change(&min_temp, min_present, datetime.min, 110, 100, COLOR_BLACK, 1, 110, 100, 130, 110, COLOR_WHITE);

						    update_change(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLACK, 1, 85, 100, 105, 110, COLOR_WHITE);

						    update_change(&date_temp, date_present, datetime.date, 85, 120, COLOR_BLACK, 1, 85, 115, 105, 135, COLOR_WHITE);

						    update_change(&month_temp, month_present, datetime.month, 112, 120, COLOR_BLACK, 1, 110, 115, 130, 135, COLOR_WHITE);

						    update_change(&year_temp, year_present, datetime.year, 139, 120, COLOR_BLACK, 1, 135, 115, 160, 135, COLOR_WHITE);

							re_write = 0;
						}
		                update_change_choose(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLUEVIOLET, 1, 85, 100, 105, 110, COLOR_WHITE);
						if (flag == 1)
						{
							choose = 0;
							alarm_changed(&alarm.hour);
			                update_change_choose(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_RED, 1, 85, 100, 105, 110, COLOR_WHITE);

						}
					}
					else if (choose == 1)
					{
		                update_change_choose(&min_temp, min_present, datetime.min, 111, 100, COLOR_BLUEVIOLET, 1, 110, 100, 130, 110, COLOR_WHITE);
						if (flag == 1)
						{
							if(re_write == 1)
							{
							    update_change(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLACK , 1, 140, 100, 160, 110, COLOR_WHITE);

							    update_change(&min_temp, min_present, datetime.min, 110, 100, COLOR_BLACK, 1, 110, 100, 130, 110, COLOR_WHITE);

							    update_change(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLACK, 1, 85, 100, 105, 110, COLOR_WHITE);

							    update_change(&date_temp, date_present, datetime.date, 85, 120, COLOR_BLACK, 1, 85, 115, 105, 135, COLOR_WHITE);

							    update_change(&month_temp, month_present, datetime.month, 112, 120, COLOR_BLACK, 1, 110, 115, 130, 135, COLOR_WHITE);

							    update_change(&year_temp, year_present, datetime.year, 139, 120, COLOR_BLACK, 1, 135, 115, 160, 135, COLOR_WHITE);

								re_write = 0;
							}
							choose = 1;
							alarm_changed(&alarm.min);
			                update_change_choose(&min_temp, min_present, datetime.min, 111, 100, COLOR_RED, 1, 110, 100, 130, 110, COLOR_WHITE);
						}
					}
					else if (choose == 2)
					{
		                update_change_choose(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLUEVIOLET , 1, 140, 100, 160, 110, COLOR_WHITE);
						if (flag == 1)
						{
							if(re_write == 1)
							{
							    update_change(&second_temp, second_present, datetime.second, 140, 100, COLOR_BLACK , 1, 140, 100, 160, 110, COLOR_WHITE);

							    update_change(&min_temp, min_present, datetime.min, 110, 100, COLOR_BLACK, 1, 110, 100, 130, 110, COLOR_WHITE);

							    update_change(&hour_temp, hour_present, datetime.hour, 85, 100, COLOR_BLACK, 1, 85, 100, 105, 110, COLOR_WHITE);

							    update_change(&date_temp, date_present, datetime.date, 85, 120, COLOR_BLACK, 1, 85, 115, 105, 135, COLOR_WHITE);

							    update_change(&month_temp, month_present, datetime.month, 112, 120, COLOR_BLACK, 1, 110, 115, 130, 135, COLOR_WHITE);
//
//							    update_change(&year_temp, year_present, datetime.year, 139, 120, COLOR_BLACK, 1, 135, 115, 160, 135, COLOR_WHITE);

								re_write = 0;
							}
							choose = 2;
							alarm_changed(&alarm.second);
			                update_change_choose(&second_temp, second_present, datetime.second, 140, 100, COLOR_RED , 1, 140, 100, 160, 110, COLOR_WHITE);
						}
					}
					alarm_buff[0] = alarm.hour;
					alarm_buff[1] = alarm.min;
					/// luu vao FLASH
					flash_unlock();
					flash_eraser(0x801FC00);
					flash_write_arr(0x801FC00, alarm_buff, sizeof(alarm_buff));
					flash_lock();
//	        	}
	            break;
	            //		  case 4: //cai dat ngay bao thuc
	            //	            				  break;
	        case 5: // introduce yourself
	        	if(rub_screen == 1)
	        	{
	        		fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_WHITE);
	        		rub_screen = 0;
	        	}
	            draw_string(5, 20, COLOR_BLACK, 1, "BT1 de chon mode");
	            draw_fast_string(5	, 40, COLOR_BLACK, COLOR_WHITE, "BT2 de chon cai can chinh ");
	            draw_fast_string(5	, 60, COLOR_BLACK, COLOR_WHITE, "BT3 Cho phep chinh cai da chon");
	            draw_fast_string(5	, 80, COLOR_BLACK, COLOR_WHITE, "BT4 Huong dan su dung");
	            break;
	        default:
	            break;
	            //
	        }
	}
}
