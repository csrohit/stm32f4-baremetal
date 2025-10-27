/**
 * @file    gpio_port.h
 * @author  Rohit Nimkar <https://csrohit.github.io>
 * @brief   Declaration of functionality related to GPIO Port
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

#include "stm32f4xx.h"

class GPIO : private GPIO_TypeDef
{
  public:
    enum Port
    {
        PortA = GPIOA_BASE,
        PortB = GPIOB_BASE,
        PortC = GPIOC_BASE
    };

    /**
     * @brief GPIO port pins
     */
    enum PIN : uint16_t
    {
        PIN_0   = (uint16_t)0x0000, /* GPIO pin 0 */
        PIN_1   = (uint16_t)0x0001, /* GPIO pin 1 */
        PIN_2   = (uint16_t)0x0002, /* GPIO pin 2 */
        PIN_3   = (uint16_t)0x0003, /* GPIO pin 3 */
        PIN_4   = (uint16_t)0x0004, /* GPIO pin 4 */
        PIN_5   = (uint16_t)0x0005, /* GPIO pin 5 */
        PIN_6   = (uint16_t)0x0006, /* GPIO pin 6 */
        PIN_7   = (uint16_t)0x0007, /* GPIO pin 7 */
        PIN_8   = (uint16_t)0x0008, /* GPIO pin 8 */
        PIN_9   = (uint16_t)0x0009, /* GPIO pin 9 */
        PIN_10  = (uint16_t)0x000A, /* GPIO pin 10 */
        PIN_11  = (uint16_t)0x000B, /* GPIO pin 11 */
        PIN_12  = (uint16_t)0x000C, /* GPIO pin 12 */
        PIN_13  = (uint16_t)0x000D, /* GPIO pin 13 */
        PIN_14  = (uint16_t)0x000E, /* GPIO pin 14 */
        PIN_15  = (uint16_t)0x000F, /* GPIO pin 15 */
        PIN_ALL = (uint16_t)0xffff  /* Select all gpio pins */
    };

    /**
     * @brief GPIO alternate function
     */
    enum AlternateFn : uint16_t
    {
        AF_0   = (uint16_t)0x0000, /* GPIO pin 0 */
        AF_1   = (uint16_t)0x0001, /* GPIO pin 1 */
        AF_2   = (uint16_t)0x0002, /* GPIO pin 2 */
        AF_3   = (uint16_t)0x0003, /* GPIO pin 3 */
        AF_4   = (uint16_t)0x0004, /* GPIO pin 4 */
        AF_5   = (uint16_t)0x0005, /* GPIO pin 5 */
        AF_6   = (uint16_t)0x0006, /* GPIO pin 6 */
        AF_7   = (uint16_t)0x0007, /* GPIO pin 7 */
        AF_8   = (uint16_t)0x0008, /* GPIO pin 8 */
        AF_9   = (uint16_t)0x0009, /* GPIO pin 9 */
        AF_10  = (uint16_t)0x000A, /* GPIO pin 10 */
        AF_11  = (uint16_t)0x000B, /* GPIO pin 11 */
        AF_12  = (uint16_t)0x000C, /* GPIO pin 12 */
        AF_13  = (uint16_t)0x000D, /* GPIO pin 13 */
        AF_14  = (uint16_t)0x000E, /* GPIO pin 14 */
        AF_15  = (uint16_t)0x000F, /* GPIO pin 15 */
        AF_ALL = (uint16_t)0xffff  /* Select all gpio pins */
    };

    /**
     * @brief GPIO logical pin state
     *
     */
    enum PinState : uint8_t
    {
        LOW  = (uint8_t)0x00, /* Pin state logical LOW */
        HIGH = (uint8_t)0x01  /* Pin state logical HIGH */
    };

    enum PinMode
    {
        INPUT  = 0x00,
        OUTPUT = 0x01, /* General Purpose Output */
        ALT    = 0x02, /* Alternate Function */
        ANALOG = 0x03  /* Analog mode */
    };

    enum OutputSpeed
    {
        OSPEED_LOW      = 0x00,
        OSPEED_MEDIUM   = 0x01, /* General Purpose Output */
        OSPEED_HIGH     = 0x02, /* Alternate Function */
        OSPEED_VERYHIGH = 0x03  /* Analog mode */
    };

    enum OutputType
    {
        OTYPE_PUSHPULL  = 0x00, /* Push-Pull (reset-state) */
        OTYPE_OPENDRAIN = 0x01  /* Open Drain (reset-state) */
    };

    enum PullUpPullDown
    {
        PUPD_NONE     = 0x00U, /* No pull-up, pull-down */
        PUPD_PULLUP   = 0x01U, /* Pull Up */
        PUPD_PULLDOWN = 0x02U, /* Pull Down */
        PUPD_RESERVED = 0x03U  /* Reserved */
    };

  public:
    /**
     * @brief
     * Initialize port and enable clock
     */
    GPIO()
    {
        this->enableClock();
    }

    /**
     * @brief Overload placement new operator
     */
    void* operator new(size_t, Port port)
    {
        return reinterpret_cast<void*>(port);
    }

    /**
     * @brief Enable clock for the instantiated port
     */
    void enableClock()
    {
        if (this == reinterpret_cast<GPIO*>(PortA))
        {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        }
        else if (this == reinterpret_cast<GPIO*>(PortB))
        {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
        }
        else if (this == reinterpret_cast<GPIO*>(PortC))
        {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
        }
    }

    /**
     * @brief disable clock for the port to save power
     */
    void disableClock()
    {
        if (this == reinterpret_cast<GPIO*>(PortA))
        {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
        }
        else if (this == reinterpret_cast<GPIO*>(PortB))
        {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
        }
        else if (this == reinterpret_cast<GPIO*>(PortC))
        {
            RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
        }
    }

    void setPinMode(PIN pin, PinMode mode)
    {
        // clear previously set mode if any
        MODER &= ~((0x03U) << (pin << 1));
        MODER |= ((mode) << (pin << 1));
    }

    void setOutputSpeed(PIN pin, OutputSpeed speed)
    {
        // clear previously set speed if any
        OSPEEDR &= ~((0x03U) << (pin << 1));
        OSPEEDR |= ((speed) << (pin << 1));
    }

    void setAlternateFunction(PIN pin, AlternateFn altFn)
    {
        if (pin < PIN_8)
        {
            AFR[0] &= ~((0x0FU) << (pin << 2));
            AFR[0] |= ((altFn) << (pin << 2));
        }
        else
        {
            AFR[1] &= ~((0x0FU) << ((pin - 8) << 2));
            AFR[1] |= ((altFn) << ((pin - 8) << 2));
        }
    }

    void setOutputType(PIN pin, OutputType type)
    {
        OTYPER &= ~(0x01U << pin);
        OTYPER |= type << pin;
    }

    void setPullUpPullDown(PIN pin, PullUpPullDown pupd)
    {
        PUPDR &= ~(0x03U << (pin << 1));
        PUPDR |= pupd << (pin << 1);
    }

    void togglePin(PIN pin)
    {
        ODR ^= 1 << pin;
    }

    /**
     * @brief Destroy the GPIO object
     *
     */
    ~GPIO()
    {
        this->disableClock();
    }
};
