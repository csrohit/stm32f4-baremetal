/**
 * @file        main.c
 * @description Scan for connected I2C devices and log device address
 * @author      Rohit Nimkar
 * @version     1.0
 * @date        2024-07-07
 * @copyright   Copyright
 * 2024 Rohit Nimkar
 *
 * @attention
 *  Use of this source code is governed by a BSD-style
 *  license that can be found in the LICENSE file or at
 *  opensource.org/licenses/BSD-3-Clause
 */

#include <stdio.h>

#include "gpio.h"
#include "i2c.h"
#include "timer.h"
#include "usart.h"
#include "oled.h"
#include "horse_anim.h"

const char* str = "I2C Scanner\r\n"; /**< Initial string */
char        buffer[128];             /**< Buffer for storing msg */
char        zz[10];

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODER13;

    GPIOC->MODER |= GPIO_MODER_MODER13_0;

    USARTInit(115200U);

    SysTick_Config(16000);

    I2CInit();

    USARTTxBuffer(str);

    GPIOToggle(GPIOC, GPIO_ODR_OD13);

    I2CInit();

    SSD1306_WRITECOMMAND(0xAE); /* Turn Off display */
    SSD1306_WRITECOMMAND(0x20); /* Set memory addressing mode */
    SSD1306_WRITECOMMAND(0x00); /* Set Page Addressing mode */
    SSD1306_WRITECOMMAND(0xB0); /* Set Page start address */
    SSD1306_WRITECOMMAND(0x00); /* Lower column start address */
    SSD1306_WRITECOMMAND(0x10); /* Upper column start address */
    SSD1306_WRITECOMMAND(0xAF); /*  Turn On Display*/
    SSD1306_WRITEDATA(0xff);

    SSD1306_WRITECOMMAND(0x00); /* Lower column start address */
    SSD1306_WRITECOMMAND(0x10); /* Upper column start address */
    for (uint8_t page = 0xB0; page <= 0xB7; ++page)
    {
        for (uint8_t i = 00; i <= 0x7f; ++i)
        {
            SSD1306_WRITEDATA(0x00);
            DelayMs(10);
        }
    }

    // SSD1306_WRITECOMMAND(0xB0); /* Set Page start address */
    for (uint8_t page = 0xB0; page <= 0xB7; ++page)
    {
        for (uint8_t i = 00; i <= 0x7f; ++i)
        {
            SSD1306_WRITEDATA(0xff);
            DelayMs(10);
        }
    }

    DelayMs(2000);
    SSD1306_Init();
    SSD1306_GotoXY(0, 0);

    SSD1306_Puts("SSD1306", &Font_7x10, 1);

    SSD1306_GotoXY(0, 10);

    SSD1306_Puts("github.com/csrohit", &Font_7x10, 1);

    SSD1306_GotoXY(0, 30);

    SSD1306_Puts("OLED Display", &Font_7x10, 1);

    SSD1306_GotoXY(0, 50);

    SSD1306_Puts("Bare Metal Code", &Font_7x10, 1);

    SSD1306_UpdateScreen(); // display

    // DelayMs(2000);
    //
    // SSD1306_ScrollRight(0, 7); // scroll entire screen
    //
    // DelayMs(2000); // 2 sec
    //
    // SSD1306_ScrollLeft(0, 7); // scroll entire screen
    //
    // DelayMs(2000); // 2 sec
    //
    // SSD1306_Stopscroll();
    //
    // SSD1306_ScrollRight(0x00, 0x0f); // scroll entire screen right
    //
    // DelayMs(2000);
    //
    // SSD1306_ScrollLeft(0x00, 0x0f); // scroll entire screen left
    //
    // DelayMs(2000);
    //
    // SSD1306_Scrolldiagright(0x00, 0x0f); // scroll entire screen diagonal right
    //
    // DelayMs(2000);
    //
    // SSD1306_Scrolldiagleft(0x00, 0x0f); // scroll entire screen diagonal left
    //
    // DelayMs(2000);
    //
    // SSD1306_Stopscroll(); // stop scrolling. If not done, screen will keep on scrolling
    //
    SSD1306_InvertDisplay(1); // invert the display

    DelayMs(2000);

    SSD1306_InvertDisplay(0); // normalize the display

    DelayMs(2000);
    SSD1306_Clear();
    SSD1306_GotoXY(0, 0);
    SSD1306_Puts("variable", &Font_7x10, 1);
    SSD1306_UpdateScreen();

    for (int i = 0; i < 100; i++)
    {
        sprintf(zz, "%i", i);
        SSD1306_GotoXY(10, 30);
        SSD1306_Puts(zz, &Font_7x10, 1);
        SSD1306_UpdateScreen();
        DelayMs(100);
    }

    SSD1306_Clear();
    SSD1306_DrawBitmap(0, 0, mj, 128, 64, 1);
    SSD1306_UpdateScreen();
    while (1)
    {
        // SSD1306_Clear();
        // SSD1306_DrawBitmap(0, 0, mj, 128, 64, 1);
        // SSD1306_UpdateScreen();
        continue;
        SSD1306_Clear();
        SSD1306_DrawBitmap(0, 0, horse2, 128, 64, 1);
        SSD1306_UpdateScreen();

        SSD1306_Clear();
        SSD1306_DrawBitmap(0, 0, horse3, 128, 64, 1);
        SSD1306_UpdateScreen();

        SSD1306_Clear();
        SSD1306_DrawBitmap(0, 0, horse4, 128, 64, 1);
        SSD1306_UpdateScreen();

        SSD1306_Clear();
        SSD1306_DrawBitmap(0, 0, horse5, 128, 64, 1);
        SSD1306_UpdateScreen();

        SSD1306_Clear();
        SSD1306_DrawBitmap(0, 0, horse6, 128, 64, 1);
        SSD1306_UpdateScreen();

        SSD1306_Clear();
        SSD1306_DrawBitmap(0, 0, horse7, 128, 64, 1);
        SSD1306_UpdateScreen();

        SSD1306_Clear();
        SSD1306_DrawBitmap(0, 0, horse8, 128, 64, 1);
        SSD1306_UpdateScreen();

        SSD1306_Clear();
        SSD1306_DrawBitmap(0, 0, horse9, 128, 64, 1);
        SSD1306_UpdateScreen();

        SSD1306_Clear();
        SSD1306_DrawBitmap(0, 0, horse10, 128, 64, 1);
        SSD1306_UpdateScreen();

        // while (1)
        // {
        //     GPIOToggle(GPIOC, GPIO_ODR_OD13);
        //     for (uint8_t address = 0x01; address < 128; ++address)
        //     {
        //         int res = I2CIsDeviceReady(address);
        //         if (0 == res)
        //         {
        //             sprintf(buffer, "Device Found at address %#x\r\n", address);
        //             USARTTxBuffer(buffer);
        //         }
        //
        //         DelayMs(20);
        //     }
        //     DelayMs(5000);
        // }
    }
}
