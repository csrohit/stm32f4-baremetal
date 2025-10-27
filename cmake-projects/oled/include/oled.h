/**
 * @file     oled.h
 * @author   Rohit Nimkar <https://csrohit.github.io>
 * @brief    Declaration of SSD1306 functionality
 * @version  1.0
 *
 * @copyright Copyright (c) 2025
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 */
#pragma once

#include "fonts.h"
#include "i2c.h"
#include <stdint.h>


typedef enum
{
    SSD1306_COLOR_BLACK = 0x00, /*!< Black color, no pixel */
    SSD1306_COLOR_WHITE = 0x01  /*!< Pixel is set. Color depends on LCD */
} SSD1306_COLOR_t;

/* Private SSD1306 structure */
typedef struct
{
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t  Inverted;
    uint8_t  Initialized;
} SSD1306_t;

/* Private variable */
static SSD1306_t oled;

#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A
#define SSD1306_DEACTIVATE_SCROLL                    0x2E // Stop scroll
#define SSD1306_ACTIVATE_SCROLL                      0x2F // Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3 // Set scroll range

#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7


// #define SSD1306_I2C_ADDR 0x3C
/* Write command */
#define SSD1306_WRITECOMMAND(command) I2C_SendByte(SSD1306::DEV_ADDR, 0x00, (command))
/* Write data */
#define SSD1306_WRITEDATA(data) I2C_SendByte(SSD1306::DEV_ADDR, 0x40, (data))
/* Absolute value */
#define ABS(x) ((x) > 0 ? (x) : -(x))


#ifndef SSD1306_H
#define SSD1306_H

/**
 * This SSD1306 LCD uses I2C for communication
 *
 * Library features functions for drawing lines, rectangles and circles.
 *
 * It also allows you to draw texts and characters using appropriate functions provided in library.
 *
 * Default pinout
 *
SSD1306    |STM32F411RE  |DESCRIPTION

VCC        |3.3V         |
GND        |GND          |
SCL        |PB8          |Serial clock line
SDA        |PB9          |Serial data line
 */

#include "stm32f4xx.h" // Device header

/* I2C address */
#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR 0x3C
// #define SSD1306_I2C_ADDR       0x7A
#endif

/* SSD1306 settings */
/* SSD1306 width in pixels */
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH 128
#endif
/* SSD1306 LCD height in pixels */
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT 64
#endif

uint8_t SSD1306_Init(void);

void SSD1306_UpdateScreen(void);

void SSD1306_ToggleInvert(void);

void SSD1306_Fill(SSD1306_COLOR_t Color);

void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);

void SSD1306_GotoXY(uint16_t x, uint16_t y);

char SSD1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color);

char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);

void SSD1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c);

void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);

void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);

void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);

void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);

void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);

void ssd1306_I2C_Init();

void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);

void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, char* data, uint16_t count);

void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color);

void SSD1306_ScrollRight(uint8_t start_row, uint8_t end_row);

void SSD1306_ScrollLeft(uint8_t start_row, uint8_t end_row);

void SSD1306_Scrolldiagright(uint8_t start_row, uint8_t end_row);

void SSD1306_Scrolldiagleft(uint8_t start_row, uint8_t end_row);

void SSD1306_Stopscroll(void);

// inverts the display i = 1->inverted, i = 0->normal

void SSD1306_InvertDisplay(int i);

// clear the display

void SSD1306_Clear(void);

#endif

class SSD1306
{
  public:
    static constexpr uint8_t HEIGHT   = 64U;
    static constexpr uint8_t WIDTH    = 128U;
    static constexpr uint8_t DEV_ADDR = 0x3CU;

    SSD1306(I2C& i2cDevice) : i2cDev(i2cDevice)
    {
    }

    void Init()
    {
        /* Init LCD */
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xAE); // display off
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x20); // Set Memory Addressing Mode
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x00); // 00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xB0); // Set Page Start Address for Page Addressing Mode,0-7
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xC8); // Set COM Output Scan Direction
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x00); //---set low column address
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x10); //---set high column address
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x40); //--set start line address
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x81); //--set contrast control register
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xFF);
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xA1); //--set segment re-map 0 to 127
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xA6); //--set normal display
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xA8); //--set multiplex ratio(1 to 64)
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x3F); //
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xA4); // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xD3); //-set display offset
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x00); //-not offset
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xD5); //--set display clock divide ratio/oscillator frequency
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xF0); //--set divide ratio
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xD9); //--set pre-charge period
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x22); //
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xDA); //--set com pins hardware configuration
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x12);
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xDB); //--set vcomh
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x20); // 0x20,0.77xVcc
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x8D); //--set DC-DC enable
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0x14); //
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xAF); //--turn on SSD1306 panel

        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, SSD1306_DEACTIVATE_SCROLL);

        // /* Clear screen */
        // SSD1306_Fill(SSD1306_COLOR_BLACK);
        //
        // /* Update screen */
        // SSD1306_UpdateScreen();

        /* Set default values */
        oled.CurrentX = 0;
        oled.CurrentY = 0;

        /* Initialized OK */
        oled.Initialized = 1;
    }

  private:
    I2C& i2cDev;
};
