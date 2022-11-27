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
#include <string.h>
#include "config.h"
#include "headphone.h"
#include "headphone_pio.pio.h"
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "info.h"
#include "usb.h"

uint16_t headphone_buffer[MEMPHIS_WS_HEADPHONE_BUFFER_ENTRIES * MEMPHIS_WS_HEADPHONE_BUFFER_SAMPLES];
volatile uint32_t headphone_buffer_idx;
volatile uint32_t headphone_buffer_idx_usb;
uint32_t headphone_dma_channel;
static bool last_headphone_active;

void ws_headphone_init(void) {
    last_headphone_active = false;
    gpio_deinit(MEMPHIS_WS_HDPN_DETECT_PIN);

    uint offset = pio_add_program(pio0, &headphone_pio_program);
    uint sm = pio_claim_unused_sm(pio0, true);
    headphone_pio_program_init(pio0, sm, offset, MEMPHIS_WS_HDPN_DATA_PIN);

    // pio_sm_clear_fifos(pio0, sm);
    // pio_sm_restart(pio0, sm);

    pio_sm_set_enabled(pio0, sm, true);

    headphone_buffer_idx = 0;
    headphone_buffer_idx_usb = 0;
    memset(headphone_buffer, 0, sizeof(headphone_buffer));

    headphone_dma_channel = dma_claim_unused_channel(true);

    {
        dma_channel_config c = dma_channel_get_default_config(headphone_dma_channel);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
        channel_config_set_read_increment(&c, false);
        channel_config_set_write_increment(&c, true);
        channel_config_set_dreq(&c, pio_get_dreq(pio0, sm, false));

        dma_channel_configure(headphone_dma_channel, &c,
            NULL,
            &pio0->rxf[sm],
            MEMPHIS_WS_HEADPHONE_BUFFER_FRAMES,
            false
        );
    }

    dma_channel_set_irq0_enabled(headphone_dma_channel, true);
    irq_set_exclusive_handler(DMA_IRQ_0, usb_audio_dma_callback);
    irq_set_enabled(DMA_IRQ_0, true);

    dma_hw->ints0 = 1u << headphone_dma_channel;
    dma_channel_set_write_addr(headphone_dma_channel, headphone_buffer, true);
}

void ws_headphone_set_active(bool active) {
    if (active != last_headphone_active) {
#ifdef MEMPHIS_DEBUG
        printf("ef: headphone -> %d\n", active ? 0 : 1);
#endif
        if (active) {
            gpio_init(MEMPHIS_WS_HDPN_DETECT_PIN);
            gpio_set_dir(MEMPHIS_WS_HDPN_DETECT_PIN, GPIO_OUT);
            gpio_put(MEMPHIS_WS_HDPN_DETECT_PIN, 0);
        } else {
            gpio_deinit(MEMPHIS_WS_HDPN_DETECT_PIN);
        }
        last_headphone_active = active;
    }
}
