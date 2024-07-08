/**
 * @file        main.c
 * @description Scan for connected I2C devices and log device address
 * @author      Rohit Nimkar
 * @version     1.0
 * @date        2024-07-07
 * @copyright   Copyright 2024 Rohit Nimkar
 *
 * @attention
 *  Use of this source code is governed by a BSD-style
 *  license that can be found in the LICENSE file or at
 *  opensource.org/licenses/BSD-3-Clause
 */

#include <stdio.h>

#include "stm32f4xx.h"
#include "gpio.h"
#include "i2c.h"
#include "timer.h"
#include "usart.h"

const char *str = "I2C Scanner\r\n"; /**< Initial string */
char        buffer[128];             /**< Buffer for storing msg */

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    GPIOC->MODER |= GPIO_MODER_MODER13_0;

    USARTInit(115200U);

    SysTick_Config(16000);

    I2CInit();

    USARTTxBuffer(str);
    while (1)
    {
        GPIOToggle(GPIOC, GPIO_ODR_OD13);
        for (uint8_t address = 0x01; address < 128; ++address)
        {
            int res = I2CIsDeviceReady(address);
            if (0 == res)
            {
                sprintf(buffer, "Device Found at address %#x\r\n", address);
                USARTTxBuffer(buffer);
            }

            DelayMs(20);
        }
        DelayMs(2000);
    }
}
