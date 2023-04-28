/*
 * function.c
 *
 *  Created on: Apr 27, 2023
 *      Author: joaoa
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usart.h"
#include "gpio.h"
#include "function.h"
#include "stm32f7xx_hal.h"


#define FALSE 0
#define TRUE 1
#define FIFO_LEN 512

uint8_t delim_1[1], delim_2[] = " ";
uint8_t rx_data = 0, tx_data = 0, new_com = 0, rx_buffer[FIFO_LEN], tx_buffer[FIFO_LEN], tx_flag = FALSE, val_com_flag = FALSE;
volatile uint16_t w_rx_bindex = 0, r_tx_bindex = 0,  r_rx_bindex = 0, w_tx_bindex = 0;
char *comando, *token, *aux_token, *memo_comando, *memo_valid_comando, *message, temp_arr[20], *memory_ptr;

void uart_commands(void){
	static machine_state state = state_stand_by;
	char *com_arr[] = {"ON"};

 		if(((w_rx_bindex-r_rx_bindex) != 0) && (new_com >0) ){

			if((*memo_comando != '$')&& (val_com_flag)){
				memo_valid_comando = (char*)malloc(strlen(memo_comando)+1);
				strcpy (memo_valid_comando,memo_comando);
			}

			comando = _my_strtok(&rx_buffer[r_rx_bindex&(FIFO_LEN-1)], delim_1[0]);
			memo_comando = (char*)malloc(strlen(comando)+1);//+1 para o caractere '\0'
			strcpy (memo_comando,comando);
			r_rx_bindex += (strlen(comando)+1);
			token = strtok(comando, delim_2);
			_push_message(memo_comando);
			append_char(delim_1[0]);

			switch(find_com(com_arr, token, 27)){
			case 0:
				if (state == state_stand_by || state == state_yellow){
						//Start PWM
						//Start medidodres de tem
					turn_on_heater();
					break;
				}
				else
					_push_message("Erro");

				break;
				default:
					_push_message("INVALID COMMAND!\n");
					 val_com_flag = FALSE;
					break;
			}
			new_com--; //Limpa a flag de novo comando
			append_char(delim_1[0]);
			//append_char('>');
			start_tx();
	}
 	if(tx_flag){
 		start_tx();
 		tx_flag = FALSE;
 	}
}
void _push_message(char *message){

	char *aux_ptr;
	uint8_t i = 0;
	aux_ptr = message;

	for (i=0; i<strlen(message); i++){

		 tx_buffer[w_tx_bindex&(FIFO_LEN-1)] = *aux_ptr;
		  aux_ptr++;
		  w_tx_bindex++;
	}
}
void append_char(char caract){ // ACRESCENTA UM CARRIAGE RETURN NO TERMINAL

	tx_buffer[w_tx_bindex&(FIFO_LEN-1)] = caract;
	w_tx_bindex++;
}
void start_tx(){

	if (USART3->ISR & USART_ISR_TC){// Transmission Complete (TC) É ATIVADA QUANDO A TRANSMISSÃO É CONCLUIDA - CASO NAO ESTEJA CONCLUIDA NAO SE DEVE INVOCAR NOVAMENTE HAL_UART_Transmit_IT()
		HAL_UART_Transmit_IT(&huart3, (uint8_t *)&tx_buffer[r_tx_bindex&(FIFO_LEN-1)],1);
		r_tx_bindex++;

	}
}
char* _my_strtok(char* str, uint8_t delimiter){
	uint8_t i=0;
	for(i=0; str[i] != delimiter; i++){
		i&= (FIFO_LEN-1);
		temp_arr[i] = str[i];

	}

	temp_arr[i] = '\0';
	return temp_arr;
}
uint8_t find_com(char *com_array[], char*token, uint8_t arr_len){

	uint8_t i = 0;
	while((strcmp(com_array[i], token))){
		if(i == (arr_len-1)){
			i = -1;
			break;
		}
		i++;
	}
	return i;
}
