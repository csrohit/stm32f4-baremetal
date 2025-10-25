/**
 * @file     main.cpp
 * @author   Rohit Nimkar <https://csrohit.github.io>
 * @brief    I2c Device Scanner
 * @version  1.0
 *
 * @copyright Copyright (c) 2025
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 */

#include "stm32f4xx.h"
#include <stdint.h>

#include "gpio_port.h"
#include "system.h"

int main(void)
{
    GPIO& portc = *new (GPIO::PortC) GPIO;

    portc.enableClock();
    portc.setPinMode(GPIO::PIN_13, GPIO::PinMode::OUTPUT);

    SysTick_Config(16000);

    while (1)
    {
        portc.togglePin(GPIO::PIN_13);
        delay_ms(100);
    }
}
