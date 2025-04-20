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

#include "stm32_compat.h"

static void cdc_init_rcc (void) {
#if defined(STM32F103x6)
    /* set flash latency 1WS */
    _BMD(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_1);
    /* use PLL 48MHz clock from 8Mhz HSI */
    _BMD(RCC->CFGR,
         RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC | RCC_CFGR_USBPRE,
         RCC_CFGR_PLLMULL12 | RCC_CFGR_USBPRE);
    _BST(RCC->CR, RCC_CR_PLLON);
    _WBS(RCC->CR, RCC_CR_PLLRDY);
    /* switch to PLL */
    _BMD(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    _WVL(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_PLL);
#elif defined(STM32F429xx) || defined(STM32F405xx) \
    || defined(STM32F401xC) || defined(STM32F401xE)  || defined(STM32F411xE)
    /* set flash latency 2WS */
    _BMD(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_2WS);
    /* setting up PLL 16MHz HSI, VCO=144MHz, PLLP = 72MHz PLLQ = 48MHz  */
    _BMD(RCC->PLLCFGR,
        RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLP,
        _VAL2FLD(RCC_PLLCFGR_PLLM, 8) | _VAL2FLD(RCC_PLLCFGR_PLLN, 72) | _VAL2FLD(RCC_PLLCFGR_PLLQ, 3));
    /* enabling PLL */
    _BST(RCC->CR, RCC_CR_PLLON);
    _WBS(RCC->CR, RCC_CR_PLLRDY);
    /* Setup CFGR to PLL*/
    /*                        APB1  |   APB2  */
    /* STM32F411             <50Mhz | <100MHz */
    /* STM32F429             <45MHz |  <90MHz */
    /* STM32F405, STM32F401  <42MHz |  <84MHz */
    _BMD(RCC->CFGR, RCC_CFGR_SW | RCC_CFGR_PPRE1, RCC_CFGR_SW_PLL | RCC_CFGR_PPRE1_DIV2);
    _WVL(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_PLL);
    #if defined(USBD_PRIMARY_OTGHS)
    /* enabling GPIOB and setting PB13, PB14 and PB15 to AF11 (USB_OTG2FS) */
    _BST(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
    #if defined(USBD_VBUS_DETECT)
    _BST(GPIOB->AFR[1], (0x0C << 24) | (0x0C << 28) | (0x0C << 20));
    _BMD(GPIOB->MODER, (0x03 << 28) | (0x03 << 30) | (0x03 << 26), (0x02 << 28) | (0x02 << 30) | (0x02 << 26));
    #else //defined(USBD_VBUS_DETECT)
    _BST(GPIOB->AFR[1], (0x0C << 24) | (0x0C << 28));
    _BMD(GPIOB->MODER, (0x03 << 28) | (0x03 << 30), (0x02 << 28) | (0x02 << 30));
    #endif //defined(USBD_VBUS_DETECT)
    #else  //defined(USBD_PRIMARY_OTGHS)
    /* enabling GPIOA and setting PA11 and PA12 to AF10 (USB_FS) */
    _BST(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
    _BST(GPIOA->AFR[1], (0x0A << 12) | (0x0A << 16));
    _BMD(GPIOA->MODER, (0x03 << 22) | (0x03 << 24), (0x02 << 22) | (0x02 << 24));
    #endif //defined(USBD_PRIMARY_OTGHS)
#elif defined(STM32H743xx)

    /* Enable USB supply */
    _BST(PWR->CR3, PWR_CR3_SCUEN | PWR_CR3_LDOEN | PWR_CR3_USB33DEN);

    /* Enable HSI48 and use as USB PHY clock */
    _BST(RCC->CR, RCC_CR_HSI48ON);
    _WBS(RCC->CR, RCC_CR_HSI48RDY);
    _BMD(RCC->D2CCIP2R, RCC_D2CCIP2R_USBSEL, 3 << RCC_D2CCIP2R_USBSEL_Pos);

    /* enabling GPIOA and setting PA11 and PA12 to AF10 (USB_FS) */
    _BST(RCC->AHB4ENR, RCC_AHB4ENR_GPIOAEN);
    _BMD(GPIOA->MODER, (0x03 << 22) | (0x03 << 24), (0x02 << 22) | (0x02 << 24));
    _BST(GPIOA->AFR[1], (0x0A << 12) | (0x0A << 16));
#else
    #error Not supported
#endif
}

void __libc_init_array(void) {

}

void SystemInit(void) {
    cdc_init_rcc();
}
