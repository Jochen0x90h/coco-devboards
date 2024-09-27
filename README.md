# CoCo Development Boards

This project contains clock initialization and include header files that are specific to various development boards

## Import
Add coco-devboards/\<version> to your conanfile where version corresponds to the git tags

## Features
* Board specific implementations of SystemInit() that set up the clock and start a timer for loop::now(), loop::sleep() and other time dependent functions

## Supported Boards
* Native
  * native
    * Dummy board for native operating system support
  * emu
    * Dummy board for graphical emulator
* nRF52
  * nrf52840
    * [nRF52840 MDK USB Dongle](https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/)
* STM32F0
  * stm32f051x8
    * [STM32F051 Discovery Kit](https://www.st.com/en/evaluation-tools/stm32f0discovery.html)
* STM32F4
  * stm32f401xe
    * [NUCLEO-F401RE](https://www.st.com/en/evaluation-tools/nucleo-f401re.html)
* STM32C0
  * stm32c031xx
    * [NUCLEO-C031C6](https://www.st.com/en/evaluation-tools/nucleo-c031c6.html)
* STM32G4
  * stm32g431xx
    * [NUCLEO-G431RB](https://www.st.com/en/evaluation-tools/nucleo-g431rb.html)
  * stm32g474xx
    * [NUCLEO-G474RE](https://www.st.com/en/evaluation-tools/nucleo-g474re.html)
