/*
 * ubx.c
 *
 *  Created on: Mar 30, 2022
 *      Author: dirac
 */


/*
 * zoe_m8q.c
 *
 *  Created on: Jul 2, 2021
 *      Author: erdem
 */

//Bu script Ublox Zoe M8Q haberleşmesi amaçlı yazılmıştır.
//İstek datası POSLLH 0xB5,0x62,0x01,0x02,0x00,0x00,0x03,0xA'dır.

#include"zoe_m8q.h"
#include"stm32f7xx.h"
#include"stm32f7xx_hal.h"
#include"math.h"
int i,j;
uint8_t request_posllh_array[8] = {0xB5,0x62,0x01,0x02,0x00,0x00,0x03,0x0A};
uint8_t request_velned_array[8] = {0xB5,0x62,0x01,0x12,0x00,0x00,0x13,0x3A};

zoe_m8q zoe;

extern UART_HandleTypeDef huart4;



void zoe_llhvelned_request(void)
{
	HAL_UART_Transmit(&huart4, request_posllh_array , 8, 10);
	//HAL_UART_Transmit(&huart4, request_velned_array , 8, 1000);
}

void zoe_parse_data(void)
{


		if(zoe.rx_zoe_data[0] == 181 &&
			zoe.rx_zoe_data[1] == 98 &&
			zoe.rx_zoe_data[2] == 1 &&
			zoe.rx_zoe_data[3] == 2)
	{
	  zoe.lattitude_zoe_m8q = zoe.rx_zoe_data[10] 	    |
				  	  	  	 (zoe.rx_zoe_data[11] << 8) |
				  	  	  	 (zoe.rx_zoe_data[12] << 16)|
							 (zoe.rx_zoe_data[13] << 24);

	  zoe.longtitude_zoe_m8q= zoe.rx_zoe_data[14] 	    |
						  	 (zoe.rx_zoe_data[15] << 8) |
						  	 (zoe.rx_zoe_data[16] << 16)|
							 (zoe.rx_zoe_data[17] << 24);

	  zoe.altitude_zoe_m8q  = zoe.rx_zoe_data[22] 	    |
						  	 (zoe.rx_zoe_data[23] << 8) |
						  	 (zoe.rx_zoe_data[24] << 16)|
							 (zoe.rx_zoe_data[25] << 24);
	}

}

void ZOE(void)
{
	  zoe_llhvelned_request();
	  zoe_parse_data();
}
