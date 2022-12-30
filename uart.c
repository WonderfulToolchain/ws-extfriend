/**
 * Copyright (c) 2022 Adrian Siekierka
 *
 * ExtFriend is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * ExtFriend is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with ExtFriend. If not, see <https://www.gnu.org/licenses/>. 
 */

#include <stdio.h>
#include "config.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "info.h"
#include "usb.h"

void ws_uart_init(void) {
    uart_init(uart0, 9600);
    uart_set_format(uart0, 8, 1, UART_PARITY_NONE);
    uart_set_hw_flow(uart0, false, false);
    uart_set_fifo_enabled(uart0, true);

    gpio_set_function(MEMPHIS_WS_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(MEMPHIS_WS_UART_RX_PIN, GPIO_FUNC_UART);
    gpio_set_inover(MEMPHIS_WS_UART_RX_PIN, GPIO_OVERRIDE_INVERT);
    gpio_set_outover(MEMPHIS_WS_UART_TX_PIN, GPIO_OVERRIDE_INVERT);

    irq_set_exclusive_handler(UART0_IRQ, usb_uart_rx);
    irq_set_enabled(UART0_IRQ, true);
    uart_set_irq_enables(uart0, true, false);
}
