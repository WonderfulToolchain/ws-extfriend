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

#ifndef __HEADPHONE_H__
#define __HEADPHONE_H__

#include <stdbool.h>

void ws_headphone_init(void);
void ws_headphone_set_active(bool active);

extern uint16_t headphone_buffer[MEMPHIS_WS_HEADPHONE_BUFFER_ENTRIES * MEMPHIS_WS_HEADPHONE_BUFFER_SAMPLES];
extern volatile uint32_t headphone_buffer_idx;
extern volatile uint32_t headphone_buffer_idx_usb;
extern uint32_t headphone_dma_channel;
extern volatile bool headphone_active;

#endif /* __HEADPHONE_H__ */
