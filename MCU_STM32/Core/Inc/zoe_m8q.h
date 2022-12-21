/*
 * zoe_m8q.h
 *
 *  Created on: Jul 2, 2021
 *      Author: erdem
 */

#ifndef INC_ZOE_M8Q_H_
#define INC_ZOE_M8Q_H_

#include "math.h"
#include "string.h"
#include "stm32f7xx_hal.h"

typedef struct zoe_m8q
		{

		double longtitude_zoe_m8q;
		double lattitude_zoe_m8q;
		int32_t altitude_zoe_m8q;

		int32_t velocity_north;
		int32_t velocity_east;
		int32_t velocity_down;
		uint32_t speed_3d;
		uint32_t speed_gnd;
		uint8_t rx_zoe_data[36];
		}zoe_m8q;


void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void POLL_WDMA_ZOE(void);
void zoe_llhvelned_request(void);
void zoe_parse_data(void);
void ZOE(void);
#endif /* INC_ZOE_M8Q_H_ */
