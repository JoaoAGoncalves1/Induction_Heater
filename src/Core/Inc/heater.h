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

extern volatile machine_state state;
extern uint8_t flag_Start_Btn;

void stand_by_mode();
void turn_on_heater();

#endif /* INC_HEATER_H_ */
