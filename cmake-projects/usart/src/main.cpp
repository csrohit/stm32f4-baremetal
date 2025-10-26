/**
 * @file     main.cpp
 * @author   Rohit Nimkar <https://csrohit.github.io>
 * @brief    USART Demo
 * @version  1.0
 *
 * @copyright Copyright (c) 2025
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 */

#include "gpio_port.h"
#include "stm32f4xx.h"
#include "system.h"
#include "usart.h"
#include <stdint.h>

const char* str = "Hello From Rohit\r\n";

int main(void)
{
    GPIO& portC = *new (GPIO::Port::PortC) GPIO;
    GPIO& portA = *new (GPIO::Port::PortA) GPIO;

    portC.setPinMode(GPIO::PIN_13, GPIO::PinMode::OUTPUT);
    portA.setPinMode(GPIO::PIN_9, GPIO::ALT);
    portA.setPinMode(GPIO::PIN_10, GPIO::ALT);

    portA.setPinSpeed(GPIO::PIN_9, GPIO::SPEED_LOW);
    portA.setPinSpeed(GPIO::PIN_10, GPIO::SPEED_LOW);

    /* Set alternate functions: USART1 -> AF7 */
    portA.setAlternateFunction(GPIO::PIN_9, GPIO::AF_7);
    portA.setAlternateFunction(GPIO::PIN_10, GPIO::AF_7);

    USART& ttl = *new (USART::Usart1) USART;
    ttl.setBaudrate(USART::BR_115200);
    ttl.setTransmitterState(USART::Enabled);
    ttl.setReceiverState(USART::Enabled);
    ttl.setUsartState(USART::Enabled);

    SysTick_Config(16000);

    while (1)
    {
        portC.togglePin(GPIO::PIN_13);
        delay_ms(1000);
        ttl.tx_str(str);
    }
}
