/**
 * @file    i2c.h
 * @author  Rohit Nimkar <https://csrohit.github.io>
 * @brief   Declaration of functionality related to I2C
 * @version 1.0
 *
 * @copyright Copyright (c) 2025
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 */
#pragma once

#include <stddef.h>
#include <stdint.h>
#include "rohit.h"

#include "stm32f4xx.h"
#include "system.h"

/**
 * @brief
 *   Generates Start condition on I2C Bus
 */
static inline void I2CStart()
{
    /* Wait till I2C bus is available */
    while (I2C1->SR2 & I2C_SR2_BUSY)
    {
    }

    I2C1->CR1 |= I2C_CR1_START;

    /* Wait till hardware detects Start condition */
    while (!(I2C1->SR1 & I2C_SR1_SB))
    {
    }
}

/**
 * @brief
 *   Generates Repeated Start condition on I2C Bus
 */
static inline void I2CRepeatStart()
{
    while (!(I2C1->SR1 & I2C_SR1_TXE))
    {
        ;
    }
    I2CStart();
}

/**
 * @brief
 *   Generates Stop condition on I2C Bus
 */
static inline void I2CStop()
{
    I2C1->CR1 |= I2C_CR1_STOP;
}

/**
 * @brief
 *   Get the address of slave used for writing data
 *   The LSB of address is unset for write operation
 *
 * @param [in] slaveAddr
 *   7 bit address of slave
 *
 * @return
 *   8 bit write slaveAddr
 */
static inline uint8_t I2CGetWriteAddress(uint8_t slaveAddr)
{
    return ((slaveAddr << 1) & (~(1 << 0)));
}

/**
 * @brief
 *   Get the address of slave used for reading data
 *   The LSB of address is set for read operation
 *
 * @param [in] slaveAddr
 *   7 bit address of slave
 *
 * @return
 *   8 bit read slaveAddr
 */
static inline uint8_t I2CGetReadAddress(uint8_t slaveAddr)
{
    return ((slaveAddr << 1) | (1 << 0));
}

/**
 * @brief
 *   Sends the slave address over I2C bus
 *
 * @param [in] slaveAddr
 *   Address of slave device
 *
 * @return
 *   0 if ACK received else 1
 */
static inline int I2CSendSlaveAddress(uint8_t slaveaddr)
{
    int res = 0;

    /* Write slave address to data register */
    I2C1->DR = slaveaddr;

    /* Wait for transmit operation completion */
    while (!((I2C1->SR1 & I2C_SR1_ADDR) || (I2C1->SR1 & I2C_SR1_AF)))
    {
    }

    /* Check for acknowledgement failure */
    res = I2C1->SR1 & I2C_SR1_AF;

    /* Clear I2C_SR1_AF flag */
    I2C1->SR1 = I2C1->SR1 & ~I2C_SR1_AF;

    /* Clear I2C_SR1_ADDR flag */
    (void)I2C1->SR2;

    return res;
}

class I2C : I2C_TypeDef
{
  public:
    typedef enum I2CInstance : uint32_t
    {
        I2c1 = I2C1_BASE,
        I2c2 = I2C2_BASE,
        I2c3 = I2C3_BASE
    } i2c_t;

    /* Public Functions */
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
    int IsDeviceReady(uint8_t address)
    {
        int res = 0;
        Start();
        res = SendSlaveAddress(GetWriteAddress(address));
        Stop();
        return res;
    }

    /**
     * @brief
     *   Send data to a slave
     *
     * @pre
     *   IsDeviceReady()
     *   The address should point to a valid device connected on the bus
     *
     * @param [in] slaveAddr
     *   7 bit address of slave
     *
     * @param [in] val
     *   8 bit data to be sent
     */
    void SendData(uint8_t slaveAddr, uint8_t val)
    {
        /* Wait till transmit buffer is empty */
        while (!(SR1 & I2C_SR1_TXE))
        {
        }

        Start();
        SendSlaveAddress(GetWriteAddress(slaveAddr));

        /* Write data to DR to send */
        I2C1->DR = val;

        /* Wait till data transmission is complete */
        /* TODO: add check for NACK, as BTF is not set when NACK is received */
        while (!(SR1 & I2C_SR1_BTF))
        {
        }

        Stop();
    }

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
    void SendByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t val)
    {
        // I2CStart();
        // I2CSendSlaveAddress(I2CGetWriteAddress(slaveAddr));
        //
        // /* Write data to DR to send */
        // while (!(I2C1->SR1 & I2C_SR1_TXE))
        // {
        //     ;
        // } /*Wait until Data register empty*/
        // I2C1->DR = regAddr;
        // while (!(I2C1->SR1 & I2C_SR1_TXE))
        // {
        // }
        //
        // /* Write data to DR to send */
        // I2C1->DR = val;
        // while (!(I2C1->SR1 & I2C_SR1_BTF))
        // {
        // }
        //
        // I2CStop();
        //
        // return;
        Start();
        SendSlaveAddress(GetWriteAddress(slaveAddr));

        /* Write data to DR to send */
        while (!(SR1 & I2C_SR1_TXE))
        {
            ;
        } /*Wait until Data register empty*/
        DR = regAddr;
        while (!(SR1 & I2C_SR1_TXE))
        {
        }

        /* Write data to DR to send */
        DR = val;
        while (!(SR1 & I2C_SR1_BTF))
        {
        }

        Stop();
    }

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
     * @param [in] pVal
     *   Address of memory to store the received data
     *
     * @param [in] nBytes
     *   Number of bytes to read
     *
     * @return
     *   0 if success else 1
     */
    int I2CRecvData(uint8_t slaveAddr, uint8_t regAddr, uint8_t* pVal, int nBytes)
    {
        uint8_t val = 0;

        Start();
        SendSlaveAddress(GetWriteAddress(slaveAddr));

        /* Write data to DR to send */
        DR = regAddr;
        while (!(SR1 & I2C_SR1_BTF))
        {
        }

        RepeatStart();
        SendSlaveAddress(GetReadAddress(slaveAddr));

        /* Send ACK after reception of next byte */
        CR1 |= I2C_CR1_ACK | I2C_CR1_POS;
        for (uint8_t i = 0U; i < nBytes - 1; ++i)
        {
            while (!(SR1 & I2C_SR1_RXNE))
            {
            }
            *(pVal + i) = (uint8_t)DR;
        }

        /* Send NACK after reception of current byte */
        CR1 &= ~(I2C_CR1_ACK | I2C_CR1_POS);
        while (!(SR1 & I2C_SR1_RXNE))
        {
        }
        *(pVal + nBytes - 1) = (uint8_t)DR;
        Stop();

        return val;
    }

    /**
     * @brief
     *   Read a single byte from a slave and send NACK
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
     * @param [in] pVal
     *   Address of memory to store the received data
     *
     * @return
     *   0 if success else 1
     */
    uint8_t RecvDataNack(uint8_t slaveAddr, uint8_t regAddr, uint8_t* pVal)
    {
        uint8_t val = 0;

        Start();
        SendSlaveAddress(GetWriteAddress(slaveAddr));

        /* Write data to DR to send */
        DR = val;

        /* Wait till data transmission is complete */
        /* TODO: add check for NACK, as BTF is not set when NACK is received */
        while (!(SR1 & I2C_SR1_BTF))
        {
        }

        RepeatStart();
        SendSlaveAddress(GetReadAddress(slaveAddr));

        CR1 &= ~(I2C_CR1_ACK | I2C_CR1_POS);
        // wait until receive buffer is not empty
        while (!(SR1 & I2C_SR1_RXNE))
            ;
        // read content and clear flags
        val = (uint8_t)DR;
        return val;
    }

    /* Static Functions */
    /**
     * @brief
     *   Get the address of slave used for writing data
     *   The LSB of address is unset for write operation
     *
     * @param [in] slaveAddr
     *   7 bit address of slave
     *
     * @return
     *   8 bit write slaveAddr
     */
    static uint8_t GetWriteAddress(uint8_t slaveAddr)
    {
        return ((slaveAddr << 0x01U) & (~(0x01U << 0)));
    }

    /**
     * @brief
     *   Get the address of slave used for reading data
     *   The LSB of address is set for read operation
     *
     * @param [in] slaveAddr
     *   7 bit address of slave
     *
     * @return
     *   8 bit read slaveAddr
     */
    static uint8_t GetReadAddress(uint8_t slaveAddr)
    {
        return ((slaveAddr << 1) | (1 << 0));
    }

    I2C()
    {
        enable();

        /* Reset I2C1 peripheral */
        I2C1->CR1 = I2C_CR1_SWRST;
        I2C1->CR1 = 0;

        /* Set PCLK = 16MHZ */
        I2C1->CR2 |= (16 << I2C_CR2_FREQ_Pos);

        /* Set Fast Mode (400 KHz) */
        I2C1->CCR |= I2C_CCR_FS;

        /* Set DUTY = 0 */
        I2C1->CCR &= ~(I2C_CCR_DUTY);

        /**
         * Calculation for CCR in Fast mode (400KHz)
         * Tpclk = 1/(16MHz) = 62.5 ns
         * As Duty == 0
         *    Thigh = CCR * Tpclk
         *    Tlow  = 2 * CCR * Tpclk
         *
         * Ttotal = CCR * Tpclk + 2 * CCR * Tpclk
         * Ttotal = 3 * CCR * Tpclk
         *
         * Ttotal/(3 * Tpclk) = CCR
         *
         * as Ttotal = 1/(400KHz) = 2.5us
         *    Tpclk  = 1/(16 MHz) = 62.5ns
         *
         * CCR =  2.5us / (3 * 62.5 ns)
         * CCR = 13.33 ~= 13
         */

        I2C1->CCR |= (13 << I2C_CCR_CCR_Pos);

        /**
         *  Calculation for TRISE
         *  - Maximum allowed SCL rise time in Fast mode is 300ns
         *  TRISE = (max_rise_time/Tpclk) + 1
         *  TRISE = (300ns/62.5ns) + 1
         *  TRISE = 6
         */
        I2C1->TRISE |= (6 << I2C_TRISE_TRISE_Pos); // program Trise to 17 for 100khz

        /* Peripheral enable */
        I2C1->CR1 |= I2C_CR1_PE;
    }

    /**
     * @brief
     *   Enable clock for I2C peripheral
     */
    void enable()
    {
        if (this == reinterpret_cast<I2C*>(I2C1))
        {
            RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        }
        else if (this == reinterpret_cast<I2C*>(I2C2))
        {
            RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
        }
        else if (this == reinterpret_cast<I2C*>(I2C3))
        {
            RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
        }
    }

    /**
     * @brief
     *   Disable clock for I2C peripheral
     */
    void disable()
    {
        if (this == reinterpret_cast<I2C*>(I2C1))
        {
            RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN;
        }
        else if (this == reinterpret_cast<I2C*>(I2C2))
        {
            RCC->APB1ENR &= ~RCC_APB1ENR_I2C2EN;
        }
        else if (this == reinterpret_cast<I2C*>(I2C3))
        {
            RCC->APB1ENR &= ~RCC_APB1ENR_I2C3EN;
        }
    }

    /**
     * @brief
     *   Get reference to a I2C instance
     *
     * @param [in] usart
     *   required hardware usart instance
     *
     * @return
     *   Pointer to the USART object
     */
    void* operator new(size_t, i2c_t i2c)
    {
        return reinterpret_cast<void*>(i2c);
    }

  private:
    /**
     * @brief
     *   Generates Start condition on I2C Bus
     */
    void Start()
    {
        CR1 |= I2C_CR1_START;

        /* Wait till hardware detects Start condition */
        while (!(SR1 & I2C_SR1_SB))
        {
        }
    }

    /**
     * @brief
     *   Generates Repeated Start condition on I2C Bus
     */
    void RepeatStart()
    {
        Start();
    }

    /**
     * @brief
     *   Generates Stop condition on I2C Bus
     */
    void Stop()
    {
        CR1 |= I2C_CR1_STOP;

        /* Wait till hardware detects Stop condition */
        while (!(SR2 & I2C_SR2_BUSY))
        {
        }
    }

    /**
     * @brief
     *   Sends the slave address over I2C bus
     *
     * @param [in] slaveAddr
     *   Address of slave device
     *
     * @return
     *   0 if ACK received else 1
     */
    int SendSlaveAddress(uint8_t slaveaddr)
    {
        int res = 0;

        /* Write slave address to data register */
        DR = slaveaddr;

        /* Wait for transmit operation completion */
        while (!((SR1 & I2C_SR1_ADDR) || (SR1 & I2C_SR1_AF)))
        {
        }

        /* Check for acknowledgement failure */
        res = SR1 & I2C_SR1_AF;

        /* Clear I2C_SR1_AF flag */
        SR1 = SR1 & ~I2C_SR1_AF;

        /* Clear I2C_SR1_ADDR flag */
        (void)SR2;

        return res;
    }
};
