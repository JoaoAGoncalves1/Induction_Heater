/*
 * heater.h
 *
 *  Created on: Apr 28, 2023
 *      Author: joaoa
 */

#ifndef INC_HEATER_H_
#define INC_HEATER_H_

typedef enum machine_state_{
	state_stand_by ,	//estado de stand by
	state_green ,	//estado de trabalho
	state_yellow ,	//estado após arrefecimento
	state_red 		//estado de perigo
}machine_state;

extern uint8_t flag_Start_Btn;

void main_function(); 	//all states will be set on this function
void stand_by_mode();
void turn_on_heater();
uint8_t Increase_PWM(uint8_t duty_cycle);
uint8_t Decrease_PWM(uint8_t duty_cycle);
#endif /* INC_HEATER_H_ */
