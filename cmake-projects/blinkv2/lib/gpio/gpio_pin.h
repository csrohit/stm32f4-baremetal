/**
 * @file    gpio_pin.h
 * @author  Rohit Nimkar (nehalnimkar@gmail.com) <https://csrohit.github.io>
 * @brief   Declaration of functionality related to GPIO Pin
 * @version 1.0
 *
 * @copyright Copyright (c) 2025
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 */

#include <stdint.h>

#include "gpio_port.h"

#ifndef GPIO_PIN_H
#define GPIO_PIN_H

class GpioPin
{
  public:
    GpioPin(GPIO& port, GPIO::PIN pin) : port(port), pin(pin)
    {
    }

    void setMode(GPIO::PinMode mode)
    {
        this->port.setPinMode(pin, mode);
    }

    void setConfig(GPIO::PinConfig config)
    {
        this->port.setPinConfig(this->pin, config);
    }

  private:
    GPIO&     port;
    GPIO::PIN pin;
};

#endif // GPIO_PIN_H
