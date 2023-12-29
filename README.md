# STM32_ZephyrOS_PWM_Example
An example on how to setup the ZephyrOS Device tree overlay PWM on a bluepill board.

To build, first install Zephyr using a python virtual environment
https://learn.adafruit.com/blinking-led-with-zephyr-rtos/installing-zephyr-linux

 Then:
# Enable zephyenv virtual environment
workon zephyenv
# Source the compiler
source ~/zephyrproject/zephyr/zephyr-env.sh
# build
west build -p -b stm32_min_dev_blue
# flash board
west flash
