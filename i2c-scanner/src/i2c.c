/**
 * @file        i2c.c
 * @description I2C related function definitions
 * @author      Rohit Nimkar
 * @version     1.0
 * @date        2024-07-07
 * @copyright   Copyright 2024 Rohit Nimkar
 *
 * @attention
 *  Use of this source code is governed by a BSD-style
 *  license that can be found in the LICENSE file or at
 *  opensource.org/licenses/BSD-3-Clause
 */

#include "i2c.h"

/* Static function declaration */
/**
 * @brief
 *   Generates Start condition on I2C Bus
 */
static inline void I2CStart() __attribute__((always_inline));

/**
 * @brief
 *   Generates Repeated Start condition on I2C Bus
 */
static inline void I2CRepeatStart() __attribute__((always_inline));

/**
 * @brief
 *   Generates Stop condition on I2C Bus
 */
static inline void I2CStop() __attribute__((always_inline));

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
static inline uint8_t I2CGetWriteAddress(uint8_t slaveAddr) __attribute__((always_inline));

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
static inline uint8_t I2CGetReadAddress(uint8_t slaveAddr) __attribute__((always_inline));

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
static int I2CSendSlaveAddress(uint8_t slaveaddr) __attribute__((always_inline));

/* Static function definition */

/**
 * @brief
 *   Generates Start condition on I2C Bus
 */
static inline void I2CStart()
{
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
    I2CStart();
}

/**
 * @brief
 *   Generates Stop condition on I2C Bus
 */
static inline void I2CStop()
{
    I2C1->CR1 |= I2C_CR1_STOP;

    /* Wait till hardware detects Stop condition */
    while (!(I2C1->SR2 & I2C_SR2_BUSY))
    {
    }
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

/* Public function definition */
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
 * @param [in] val
 *   8 bit data to be sent
 */
void I2CSendData(uint8_t slaveAddr, uint8_t val)
{
    /* Wait till transmit buffer is empty */
    while (!(I2C1->SR1 & I2C_SR1_TXE))
    {
    }

    I2CStart();
    I2CSendSlaveAddress(I2CGetWriteAddress(slaveAddr));

    /* Write data to DR to send */
    I2C1->DR = val;

    /* Wait till data transmission is complete */
    /* TODO: add check for NACK, as BTF is not set when NACK is received */
    while (!(I2C1->SR1 & I2C_SR1_BTF))
    {
    }

    I2CStop();
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
int I2CRecvData(uint8_t slaveAddr, uint8_t regAddr, uint8_t *pVal, int nBytes)
{
    uint8_t val = 0;

    I2CStart();
    I2CSendSlaveAddress(I2CGetWriteAddress(slaveAddr));

    /* Write data to DR to send */
    I2C1->DR = regAddr;
    while (!(I2C1->SR1 & I2C_SR1_BTF))
    {
    }

    I2CRepeatStart();
    I2CSendSlaveAddress(I2CGetReadAddress(slaveAddr));

    /* Send ACK after reception of next byte */
    I2C1->CR1 |= I2C_CR1_ACK | I2C_CR1_POS;
    for (uint8_t i = 0U; i < nBytes - 1; ++i)
    {
        while (!(I2C1->SR1 & I2C_SR1_RXNE))
        {
        }
        *(pVal + i) = (uint8_t)I2C1->DR;
    }

    /* Send NACK after reception of current byte */
    I2C1->CR1 &= ~(I2C_CR1_ACK | I2C_CR1_POS);
    while (!(I2C1->SR1 & I2C_SR1_RXNE))
    {
    }
    *(pVal + nBytes - 1) = (uint8_t)I2C1->DR;
    I2CStop();

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
uint8_t I2CRecvDataNAck(uint8_t slaveAddr, uint8_t regAddr, uint8_t *pVal)
{
    uint8_t val = 0;

    I2CStart();
    I2CSendSlaveAddress(I2CGetWriteAddress(slaveAddr));

    /* Write data to DR to send */
    I2C1->DR = val;

    /* Wait till data transmission is complete */
    /* TODO: add check for NACK, as BTF is not set when NACK is received */
    while (!(I2C1->SR1 & I2C_SR1_BTF))
    {
    }

    I2CRepeatStart();
    I2CSendSlaveAddress(I2CGetReadAddress(slaveAddr));

    I2C1->CR1 &= ~(I2C_CR1_ACK | I2C_CR1_POS);
    // wait until receive buffer is not empty
    while (!(I2C1->SR1 & I2C_SR1_RXNE))
        ;
    // read content and clear flags
    val = (uint8_t)I2C1->DR;
    return val;
}

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
int I2CIsDeviceReady(uint8_t address)
{
    int res = 0;
    I2CStart();
    res = I2CSendSlaveAddress(I2CGetWriteAddress(address));
    I2CStop();
    return res;
}

/**
 * @brief 
 *   Initialize I2C peripheral
 */
void I2CInit()
{
    /* Enable clock for PORTB */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    /* Set Mode of PB6(SCL) as Alternate */
    GPIOB->MODER &= ~GPIO_MODER_MODE6;
    GPIOB->MODER |= GPIO_MODER_MODE6_1;

    /* Set PB6(SCL) to open-drain */
    GPIOB->OTYPER |= GPIO_OTYPER_OT6;

    /* Set PB6(SCL) to no pullup-pulldown */
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;

    /* Set identical configuration for PB7(SDA) */
    GPIOB->MODER &= ~GPIO_MODER_MODE7;
    GPIOB->MODER |= GPIO_MODER_MODE7_1;
    GPIOB->OTYPER |= GPIO_OTYPER_OT7;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD7;

    /* Set Alternate Function 4 for pin PB6(SCL) and PB7(SDA) */
    GPIOB->AFR[0] |= (4 << GPIO_AFRL_AFSEL6_Pos);
    GPIOB->AFR[0] |= (4 << GPIO_AFRL_AFSEL7_Pos);

    /* Enable clock for I2C1 */
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    /* Reset I2C1 peripheral */
    I2C1->CR1 = I2C_CR1_SWRST;
    I2C1->CR1 = 0;

    /* Set PCLK = 16MHZ */
    I2C1->CR2 |= (16 << I2C_CR2_FREQ_Pos);

    /* Set Fast Mode (400 KHz) */
    I2C1->CCR |=  I2C_CCR_FS;

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
