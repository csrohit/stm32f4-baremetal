/**
 * original author:  Tilen Majerle<tilen@majerle.eu>
 * modification for C++: Rohit Nimkar
   ----------------------------------------------------------------------
    Copyright (C) Rohit Nimkar, 2025
    Copyright (C) Husamuldeen, 2020
    Copyright (C) Tilen Majerle, 2015

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
 */

#pragma once

/**
 *
 * Default fonts library. It is used in all LCD based libraries.
 *
 * \par Supported fonts
 *
 * Currently, these fonts are supported:
 *  - 7 x 10 pixels
 *  - 11 x 18 pixels
 *  - 16 x 26 pixels
 */

#include "stdint.h"
#include "string.h"

class Fonts
{
  public:
    /**
     * @brief
     *   Font structure used on display libraries
     */
    struct FontDef_t
    {
        uint8_t         width;  // Font width in pixels
        uint8_t         height; // Font height in pixels
        const uint16_t* pData;  // Pointer to font data array
    };

    /**
     * @brief
     *   String length and height
     */
    typedef struct
    {
        uint16_t length; /*!< String length in units of pixels */
        uint16_t height; /*!< String height in units of pixels */
    } FontSize_t;

    /**
     * @brief  7 x 10 pixels font size structure
     */
    static FontDef_t Font_7x10;

    /**
     * @brief  11 x 18 pixels font size structure
     */
    static FontDef_t Font_11x18;

    /**
     * @brief  16 x 26 pixels font size structure
     */
    static FontDef_t Font_16x26;

  private:
    /**
     * @brief
     *   Calculates string length and height in units of pixels depending on string and font used
     *
     * @param str   [in]
     *   String to be checked for length and height
     * @param pSize [out]
     *   Pointer to empty @ref FONTS_SIZE_t structure where informations will be saved
     * @param pFont [in]
     *   Pointer to @ref FontDef_t font used for calculations
     *
     * @retval
     *   Pointer to string used for length and height
     */
    char* GetStringSize(char* str, FontSize_t* pSize, FontDef_t* pFont)
    {
        pSize->height = pFont->height;
        pSize->length = pFont->width * strlen(str);

        return str;
    }
};
