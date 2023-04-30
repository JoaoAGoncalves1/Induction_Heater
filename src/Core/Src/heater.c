/*
 * heater.c
 *
 *  Created on: Apr 28, 2023
 *      Author: joaoa
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heater.h"

volatile machine_state state = state_stand_by;
uint8_t flag_Start_Btn = 0;
uint8_t duty_cycle = 0;

void stand_by_mode(){
	_push_message("RESET");
	//ligar PWM//checkar temperatura
	if (flag_Start_Btn == 1){

	}
}
void turn_on_heater(){
	state = state_stand_by;
}
