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

#include "pico/stdlib.h"
#include "info.h"
#include "config.h"

void led_init(void) {
    gpio_init(MEMPHIS_LED_PIN);
    gpio_set_dir(MEMPHIS_LED_PIN, GPIO_OUT);
}

void led_set_active(uint8_t active) {
    gpio_put(MEMPHIS_LED_PIN, active ? 1 : 0);
}
