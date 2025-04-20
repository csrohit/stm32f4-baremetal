/* This file is the part of the Lightweight USB device Stack for STM32 microcontrollers
 *
 * Copyright ©2016 Dmitry Filimonchuk <dmitrystu[at]gmail[dot]com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _USB_H_
#define _USB_H_
#if defined(__cplusplus)
    extern "C" {
#endif

#include "usbd_core.h"
#if !defined(__ASSEMBLER__)
#include "usb_std.h"
#endif


#if defined(STM32F411xE) || defined(STM32F401xC) || defined(STM32F401xE)

    #define USBD_STM32F429FS
    #if !defined(__ASSEMBLER__)
    extern const struct usbd_driver usbd_otgfs;
    #endif
    #define usbd_hw usbd_otgfs

#elif defined(STM32F102x6) || defined(STM32F102xB) || \
      defined(STM32F103x6) || defined(STM32F103xB) || \
      defined(STM32F103xE) || defined(STM32F103xG) || \
      defined(STM32F302x8) || defined(STM32F302xC) || defined(STM32F302xE) || \
      defined(STM32F303xC) || defined(STM32F303xE) || \
      defined(STM32F373xC)

    #define USBD_STM32F103

    #if !defined(__ASSEMBLER__)
    extern const struct usbd_driver usbd_devfs;
    extern const struct usbd_driver usbd_devfs_asm;
    #if defined(USBD_ASM_DRIVER)
    #define usbd_hw usbd_devfs_asm
    #else
    #define usbd_hw usbd_devfs
    #endif
    #endif

#elif defined(STM32H743xx)
    #define USBD_STM32H743FS

    #if !defined(__ASSEMBLER__)
    extern const struct usbd_driver usbd_otgfs;
    #define usbd_hw usbd_otgfs
    #endif  //__ASSEMBLER__

#else
    #error Unsupported STM32 family
#endif

#if defined (__cplusplus)
    }
#endif
#endif //_USB_H_
