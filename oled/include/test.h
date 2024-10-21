/**

 * original author: Husamuldeen <https://github.com/hussamaldean>

   ----------------------------------------------------------------------
   	Copyright (C) husamuldeen, 2020

    
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

#ifndef TEST_H_
#define TEST_H_

#include "stdint.h"

void TestLines (uint8_t color);

void TestRectangles (uint8_t color);

void TestFilledRectangles (uint8_t color);

void TestFilledCircles(uint8_t radius, uint16_t color);

void TestCircles(uint8_t radius, uint16_t color);

void TestTriangles(uint8_t color);

#endif /* TEST_H_ */
