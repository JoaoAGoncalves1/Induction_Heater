/*
 * heater.c
 *
 *  Created on: Apr 28, 2023
 *      Author: joaoa
 */
#include "stm32f7xx_hal.h"
#include "tim.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heater.h"

uint8_t flag_Start_Btn = 0;

void stand_by_mode(void){
	_push_message("RESET");
	if (flag_Start_Btn == 1){
		turn_on_heater();
	}
}
void main_function(){			//só esta função é que precisa de saber o estado
	static machine_state state = state_stand_by;
	static uint8_t duty_cycle = 0;
	if (flag_Start_Btn == 1)
		state = state_green;

	switch (state){
		case state_stand_by: 	//stand_by
			stand_by_mode();
			break;
		case state_green:		//state_green

			break;
		case state_yellow: 	//state_yellow

			break;
		case state_red: 	//state_red

			break;
	}
}
void turn_on_heater(){

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

uint8_t Increase_PWM(uint8_t duty_cycle){		//mudar para outro ficheiro???

	duty_cycle += 50;
	if (duty_cycle >= 1000)
		duty_cycle = 250;

	TIM_OC_InitTypeDef sConfigOC = {0};
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = duty_cycle;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel (&htim2, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	return duty_cycle;
}
uint8_t Decrease_PWM(uint8_t duty_cycle){

	duty_cycle -= 50;
	if (duty_cycle <= 0)
		duty_cycle = 50;

	TIM_OC_InitTypeDef sConfigOC = {0};
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = duty_cycle;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel (&htim2, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	return duty_cycle;
}
