# CoCo Development Boards

This project contains clock initialization and include header files that are specific to various development boards

## Import
Add coco-devboards/\<version> to your conanfile where version corresponds to the git tags

## Features
* Board specific implementations of SystemInit() that set up the clock and start a timer for loop::now(), loop::sleep() and other time dependent functions

## Supported Boards
* Native
  * native
    * Native dummy board using drivers that print to stdout
* nRF52
  * nrf52805
  * nrf52810
  * nrf52811
  * nrf52820
  * nrf52833
  * nrf52840
    * [nRF52840 MDK USB Dongle](https://wiki.makerdiary.com/nrf52840-mdk-usb-dongle/)
* STM32F0
  * stm32f030x6
  * stm32f038xx
  * stm32f058xx
  * stm32f072xb
  * stm32f030x8
  * stm32f042x6
  * stm32f070x6
  * stm32f078xx
  * stm32f030xc
  * stm32f048xx
  * stm32f070xb
  * stm32f091xc
  * stm32f031x6
  * stm32f051x8
    * [STM32F051 Discovery Kit](https://www.st.com/en/evaluation-tools/stm32f0discovery.html)
  * stm32f071xb
  * stm32f098xx
