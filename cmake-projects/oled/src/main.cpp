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
#include <stdint.h>
#include <stdio.h>

#include "gpio_port.h"
#include "i2c.h"
#include "oled.h"
#include "stm32f4xx.h"
#include "system.h"
#include "usart.h"
#include "mj.h"

void InitStdOut()
{
    GPIO& portA = *new (GPIO::Port::PortA) GPIO;
    portA.setPinMode(GPIO::PIN_9, GPIO::ALT);
    portA.setPinMode(GPIO::PIN_10, GPIO::ALT);

    portA.setOutputSpeed(GPIO::PIN_9, GPIO::OSPEED_LOW);
    portA.setOutputSpeed(GPIO::PIN_10, GPIO::OSPEED_LOW);

    /* Set alternate functions: USART1 -> AF7 */
    portA.setAlternateFunction(GPIO::PIN_9, GPIO::AF_7);
    portA.setAlternateFunction(GPIO::PIN_10, GPIO::AF_7);

    USART& out = *new (USART::Usart1) USART;
    out.setBaudrate(USART::BR_115200);
    out.setTransmitterState(USART::Enabled);
    out.setReceiverState(USART::Enabled);
    out.setUsartState(USART::Enabled);
}

int main(void)
{
    /* Required for Printf to work */
    InitStdOut();

    GPIO& portC = *new (GPIO::Port::PortC) GPIO;
    GPIO& portB = *new (GPIO::Port::PortB) GPIO;

    portC.setPinMode(GPIO::PIN_13, GPIO::PinMode::OUTPUT);

    I2C& i2c = *new (I2C::I2c1) I2C;

    /* Set Mode of PB6(SCL) as Alternate */
    portB.setPinMode(GPIO::PIN_6, GPIO::ALT);

    /* Set Alternate Function 4 for pin PB6(SCL) */
    portB.setAlternateFunction(GPIO::PIN_6, GPIO::AF_4);

    /* Set PB6(SCL) to open-drain */
    portB.setOutputType(GPIO::PIN_6, GPIO::OTYPE_OPENDRAIN);

    /* Set PB6(SCL) to no pullup-pulldown */
    portB.setPullUpPullDown(GPIO::PIN_6, GPIO::PUPD_NONE);

    /* Set identical configuration for PB7(SDA) */
    portB.setPinMode(GPIO::PIN_7, GPIO::ALT);
    portB.setAlternateFunction(GPIO::PIN_7, GPIO::AF_4);
    portB.setOutputType(GPIO::PIN_7, GPIO::OTYPE_OPENDRAIN);
    portB.setPullUpPullDown(GPIO::PIN_7, GPIO::PUPD_NONE);

    SysTick_Config(16000);

    SSD1306 display(i2c);
    display.Init();

    i2c.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x00); //
    i2c.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x10); //--turn on SSD1306 panel
    for (uint8_t page = 0xB0; page <= 0xB7; ++page)
    {
        for (uint8_t i = 00; i <= 0x7f; ++i)
        {
            i2c.SendByte(SSD1306::DEV_ADDR, 0x40U, 0xFF); //--turn on SSD1306 panel
            delay_ms(2);
        }
    }

    // SSD1306_WRITECOMMAND(0xB0); /* Set Page start address */
    for (uint8_t page = 0xB0; page <= 0xB7; ++page)
    {
        for (uint8_t i = 00; i <= 0x7f; ++i)
        {
            i2c.SendByte(SSD1306::DEV_ADDR, 0x40U, 0x00); //--turn on SSD1306 panel
            delay_ms(2);
        }
    }

    SSD1306_GotoXY(0, 0);
    char* name = "SSD1306";
    SSD1306_Puts(name, &Font_7x10, SSD1306_COLOR_WHITE);

    SSD1306_GotoXY(0, 10);

    SSD1306_Puts("github.com/chellosrohit", &Font_7x10, SSD1306_COLOR_WHITE);

    SSD1306_GotoXY(0, 30);

    SSD1306_Puts("OLED Display", &Font_7x10, SSD1306_COLOR_WHITE);

    SSD1306_GotoXY(0, 50);

    SSD1306_Puts("Bare Metal Code", &Font_7x10, SSD1306_COLOR_WHITE);

    SSD1306_UpdateScreen(); // display
    while (1)
    {
        portC.togglePin(GPIO::PIN_13);
        delay_ms(1000);
        printf("I2C Scanner...\r\n");

        for (uint8_t address = 0x01; address < 128; ++address)
        {
            int res = i2c.IsDeviceReady(address);
            if (0 == res)
            {
                printf("Device Found at address %#x\r\n", address);
            }

            delay_ms(20);
        }
        delay_ms(5000);
    }
}
