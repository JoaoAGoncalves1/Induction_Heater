/*
 * function.h
 *
 *  Created on: Apr 27, 2023
 *      Author: joaoa
 */

#ifndef INC_FUNCTION_H_
#define INC_FUNCTION_H_

extern uint8_t rx_data, tx_data, delim_1[1], rx_buffer[], tx_buffer[], new_com,tx_flag;
extern	volatile uint16_t w_rx_bindex, r_tx_bindex, r_rx_bindex, w_tx_bindex;

typedef enum machine_state_{
	state_stand_by ,	//estado de stand by
	state_green ,	//estado de trabalho
	state_yellow ,	//estado após arrefecimento
	state_red 		//estado de perigo
}machine_state;

void uart_commands(void);
void _push_message(char *message);
void append_char(char caract);
void start_tx();
char* _my_strtok(char* str, uint8_t delimiter);
uint8_t find_com(char *com_array[], char*token, uint8_t arr_len);
#endif /* INC_FUNCTION_H_ */
