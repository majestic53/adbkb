/**
 * ADB-Keyboard
 * Copyright (C) 2018 David Jolly
 *
 * ADB-Keyboard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ADB-Keyboard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include "../include/adb.h"
#include "../include/uart.h"

#define INIT_ANIM
#define INIT_ANIM_DELAY 250
#define INIT_ANIM_MAX 4

static uint16_t INIT_ANIM_DATA[] = {
	~1, ~2, ~4, ~7, ~0,
	};

void
init(void)
{
	adb_cmd_t cmd = {};

	uart_init();

	adb_init();
	adb_reset();

	cmd.addr = ADB_ADDR_KB;
	cmd.cmd = ADB_CMD_TALK;
	cmd.reg = ADB_REG_IDENT;

	adb_send(&cmd, NULL);

#ifdef INIT_ANIM
	cmd.addr = ADB_ADDR_KB;
	cmd.cmd = ADB_CMD_LISTEN;
	cmd.reg = ADB_REG_2;

	_delay_ms(INIT_ANIM_DELAY);

	for(uint8_t iter = 0; iter <= INIT_ANIM_MAX; ++iter) {
		adb_send(&cmd, &INIT_ANIM_DATA[iter]);
		_delay_ms(INIT_ANIM_DELAY);
	}
#endif // INIT_ANIM
}

bool
poll(
	__inout adb_evt_t *evt
	)
{
	adb_cmd_t cmd = {};

	cmd.addr = ADB_ADDR_KB;
	cmd.cmd = ADB_CMD_TALK;
	cmd.reg = ADB_REG_DATA;

	adb_send(&cmd, NULL);

	return adb_recv(evt);
}

int
main(void)
{
	init();

	for(;;) {
		adb_evt_t evt = {};

		if(poll(&evt)) {

// TODO
for(int iter = 0; iter < 16; ++iter) {
	uart_send((evt.raw & 0x8000) ? '1' : '0');
	evt.raw <<= 1;
}

uart_send('\r');
uart_send('\n');
// ---

			// TODO: decode event
			// TODO: send corrisponding keycode to uart
		}
	}

	return 0;
}
