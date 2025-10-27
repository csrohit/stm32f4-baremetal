#ifndef I2C_H
#define I2C_H

/**
 * @file        i2c.h
 * @description I2C related function declarations
 * @author      Rohit Nimkar
 * @version     1.1
 * @date        2024-07-16
 * @copyright   Copyright 2024 Rohit Nimkar
 *
 * @attention
 *  Use of this source code is governed by a BSD-style
 *  license that can be found in the LICENSE file or at
 *  opensource.org/licenses/BSD-3-Clause
 */

#include <stdint.h>
#include "stm32f4xx.h"

/**
 * @brief
 *   Send data to a slave
 *
 * @pre
 *   I2CIsDeviceReady()
 *   The address should point to a valid device connected on the bus
 *
 * @param [in] slaveAddr
 *   7 bit address of slave
 *
 * @param [in] regAddr
 *   Address of register to write to
 *
 * @param [in] val
 *   8 bit data to be sent
 */
void I2C_SendByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t val);

/**
 * @brief
 *   Read Data from slave
 *
 * @pre
 *   I2CIsDeviceReady()
 *   The address should point to a valid device connected on the bus
 *
 * @param [in] slaveAddr
 *   7 bit address of slave
 *
 * @param [in] regAddr
 *   Address of register to read from
 *
 * @param [out] pVal
 *   address of variable to save read data
 */
char I2C_ReadByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t* pVal);

/**
 * @brief
 *   Write multiple bytes to a slave
 *
 * @pre
 *   I2CIsDeviceReady()
 *   The address should point to a valid device connected on the bus
 *
 * @param [in] slaveAddr
 *   7 bit address of slave
 *
 * @param [in] regAddr
 *   Address of register to start writing to
 *
 * @param [in] pVal
 *   Address of first byte
 *
 * @param [in] nBytes
 *   Number of bytes to write
 *
 * @return
 *   0 if success else 1
 */
void I2C_SendData(uint8_t slaveAddr, uint8_t regAddr, uint8_t* pVal, uint8_t bBytes);

/**
 * @brief
 *   Read multiple bytes from a slave and send ACK
 *
 * @pre
 *   I2CIsDeviceReady()
 *   The address should point to a valid device connected on the bus
 *
 * @param [in] slaveAddr
 *   7 bit address of slave
 *
 * @param [in] regAddr
 *   Address of register to read from
 *
 * @param [out] pVal
 *   Address of memory to store the received data
 *
 * @param [in] nBytes
 *   Number of bytes to read
 *
 * @return
 *   0 if success else 1
 */
int I2CRecvData(uint8_t slaveAddr, uint8_t regAddr, uint8_t* pVal, int nBytes);

/**
 * @brief
 *   Verifies if the I2C device is available at given address
 *
 * @param [in] address
 *   Address of slave device
 *
 * @return
 *   0 if success else 1
 */
int I2CIsDeviceReady(uint8_t slaveaddr);

/**
 * @brief
 *   Initialize I2C peripheral
 */
void I2CInit();

#endif /* I2C_H */
