/**
 * @file     h
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
extern char SSD1306_Buffer[];

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

class SSD1306
{
  public:
    enum DisplayMode
    {
        DISPLAY_NORMAL  = 0xA6,
        DISPLAY_INVERSE = 0xA7
    };

    enum DisplaySource
    {
        DISPLAY_ON  = 0xA5,
        DISPLAY_RAM = 0xA4
    };

    static constexpr uint8_t HEIGHT   = 64U;
    static constexpr uint8_t WIDTH    = 128U;
    static constexpr uint8_t DEV_ADDR = 0x3CU;

  private:
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t  Inverted;
    uint8_t  Initialized;
    I2C&     i2cDev;

    uint8_t FrameBuffer[WIDTH * HEIGHT / sizeof(char)];

  public:
    SSD1306(I2C& i2cDevice) : i2cDev(i2cDevice)
    {
    }

    void Init()
    {
        /* Init LCD */
        PowerOff();
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
        PowerOn();

        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, SSD1306_DEACTIVATE_SCROLL);

        // /* Clear screen */
        // SSD1306_Fill(SSD1306_COLOR_BLACK);
        //
        // /* Update screen */
        // SSD1306_UpdateScreen();

        /* Set default values */
        CurrentX = 0;
        CurrentY = 0;

        /* Initialized OK */
        Initialized = 1;
    }

    char Puts(const char* str, FontDef_t* Font, SSD1306_COLOR_t color)
    {
        /* Write characters */
        while (*str)
        {
            /* Write character by character */
            if (Putc(*str, Font, color) != *str)
            {
                /* Return error */
                return *str;
            }

            /* Increase string pointer */
            str++;
        }

        /* Everything OK, zero should be returned */
        return *str;
    }

    char Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color)
    {
        uint32_t i, b, j;

        /* Check available space in LCD */
        if (WIDTH <= (CurrentX + Font->FontWidth) || HEIGHT <= (CurrentY + Font->FontHeight))
        {
            /* Error */
            return 0;
        }

        /* Go through font */
        for (i = 0; i < Font->FontHeight; i++)
        {
            b = Font->data[(ch - 32) * Font->FontHeight + i];
            for (j = 0; j < Font->FontWidth; j++)
            {
                if ((b << j) & 0x8000)
                {
                    DrawPixel(CurrentX + j, (CurrentY + i), (SSD1306_COLOR_t)color);
                }
                else
                {
                    DrawPixel(CurrentX + j, (CurrentY + i), (SSD1306_COLOR_t)!color);
                }
            }
        }

        /* Increase pointer */
        CurrentX += Font->FontWidth;

        /* Return character written */
        return ch;
    }

    void DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color)
    {
        if (x >= WIDTH || y >= HEIGHT)
        {
            /* Error */
            return;
        }

        /* Check if pixels are inverted */
        if (Inverted)
        {
            color = (SSD1306_COLOR_t)!color;
        }

        /* Set color */
        if (color == SSD1306_COLOR_WHITE)
        {
            FrameBuffer[x + (y / 8) * WIDTH] |= 1 << (y % 8);
        }
        else
        {
            FrameBuffer[x + (y / 8) * WIDTH] &= ~(1 << (y % 8));
        }
    }

    void Refresh()
    {
        uint8_t m;

        for (m = 0; m < 8; m++)
        {
            SSD1306_WRITECOMMAND(0xB0 + m);
            SSD1306_WRITECOMMAND(0x00);
            SSD1306_WRITECOMMAND(0x10);

            /* Write multi data */
            i2cDev.SendData(DEV_ADDR, 0x40, &FrameBuffer[WIDTH * m], WIDTH);
        }
    }

    void DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, SSD1306_COLOR_t color)
    {

        int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
        uint8_t byte      = 0;

        for (int16_t j = 0; j < h; j++, y++)
        {
            for (int16_t i = 0; i < w; i++)
            {
                if (i & 7)
                {
                    byte <<= 1;
                }
                else
                {
                    byte = (*(const unsigned char*)(&bitmap[j * byteWidth + i / 8]));
                }
                if (byte & 0x80)
                {
                    DrawPixel(x + i, y, color);
                }
            }
        }
    }
    void ScrollRight(uint8_t start_row, uint8_t end_row)
    {
        SSD1306_WRITECOMMAND(SSD1306_RIGHT_HORIZONTAL_SCROLL); // send 0x26
        SSD1306_WRITECOMMAND(0x00);                            // send dummy
        SSD1306_WRITECOMMAND(start_row);                       // start page address
        SSD1306_WRITECOMMAND(0X00);                            // time interval 5 frames
        SSD1306_WRITECOMMAND(end_row);                         // end page address
        SSD1306_WRITECOMMAND(0X00);
        SSD1306_WRITECOMMAND(0XFF);
        SSD1306_WRITECOMMAND(SSD1306_ACTIVATE_SCROLL); // start scroll
    }

    void ScrollLeft(uint8_t start_row, uint8_t end_row)
    {
        SSD1306_WRITECOMMAND(SSD1306_LEFT_HORIZONTAL_SCROLL); // send 0x26
        SSD1306_WRITECOMMAND(0x00);                           // send dummy
        SSD1306_WRITECOMMAND(start_row);                      // start page address
        SSD1306_WRITECOMMAND(0X00);                           // time interval 5 frames
        SSD1306_WRITECOMMAND(end_row);                        // end page address
        SSD1306_WRITECOMMAND(0X00);
        SSD1306_WRITECOMMAND(0XFF);
        SSD1306_WRITECOMMAND(SSD1306_ACTIVATE_SCROLL); // start scroll
    }

    void Scrolldiagright(uint8_t start_row, uint8_t end_row)
    {
        SSD1306_WRITECOMMAND(SSD1306_SET_VERTICAL_SCROLL_AREA); // sect the area
        SSD1306_WRITECOMMAND(0x00);                             // write dummy
        SSD1306_WRITECOMMAND(HEIGHT);

        SSD1306_WRITECOMMAND(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
        SSD1306_WRITECOMMAND(0x00);
        SSD1306_WRITECOMMAND(start_row);
        SSD1306_WRITECOMMAND(0X00);
        SSD1306_WRITECOMMAND(end_row);
        SSD1306_WRITECOMMAND(0x01);
        SSD1306_WRITECOMMAND(SSD1306_ACTIVATE_SCROLL);
    }

    void Scrolldiagleft(uint8_t start_row, uint8_t end_row)
    {
        SSD1306_WRITECOMMAND(SSD1306_SET_VERTICAL_SCROLL_AREA); // sect the area
        SSD1306_WRITECOMMAND(0x00);                             // write dummy
        SSD1306_WRITECOMMAND(HEIGHT);

        SSD1306_WRITECOMMAND(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
        SSD1306_WRITECOMMAND(0x00);
        SSD1306_WRITECOMMAND(start_row);
        SSD1306_WRITECOMMAND(0X00);
        SSD1306_WRITECOMMAND(end_row);
        SSD1306_WRITECOMMAND(0x01);
        SSD1306_WRITECOMMAND(SSD1306_ACTIVATE_SCROLL);
    }

    void Stopscroll(void)
    {
        SSD1306_WRITECOMMAND(SSD1306_DEACTIVATE_SCROLL);
    }

    void InvertDisplay(int i)
    {
        if (i)
            SSD1306_WRITECOMMAND(SSD1306_INVERTDISPLAY);

        else
            SSD1306_WRITECOMMAND(SSD1306_NORMALDISPLAY);
    }

    void Fill(SSD1306_COLOR_t color)
    {
        /* Set memory */
        memset(FrameBuffer, (color == SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(FrameBuffer));
    }

    void GotoXY(uint16_t x, uint16_t y)
    {
        /* Set write pointers */
        CurrentX = x;
        CurrentY = y;
    }

    void Clear(void)
    {
        Fill(SSD1306_COLOR_BLACK);
        Refresh();
    }

    void SetDisplaySource(const DisplaySource source)
    {
        SendCommand(source);
    }

    void SetDisplayMode(const DisplayMode mode)
    {
        SendCommand(mode);
    }

    /*
     * @brief
     *   Display On - Normal mode
     */
    void PowerOn(void)
    {
        SSD1306_WRITECOMMAND(0x8D);
        SSD1306_WRITECOMMAND(0x14);
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xAF); // display off
    }

    /*
     * @brief
     *   Display Off - Sleep mode
     */
    void PowerOff(void)
    {
        SSD1306_WRITECOMMAND(0x8D);
        SSD1306_WRITECOMMAND(0x10);
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, 0xAE); // display off
    }

  private:
    void SendCommand(uint8_t command)
    {
        i2cDev.SendByte(SSD1306::DEV_ADDR, 0x00U, command); // display off
    }
};
