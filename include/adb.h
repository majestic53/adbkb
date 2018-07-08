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

#ifndef ADB_H_
#define ADB_H_

#include "./def.h"

enum {
	ADB_ADDR_KB = 0x02,
};

enum {
	ADB_CMD_LISTEN = 0x02,
	ADB_CMD_TALK,
};

enum {
	ADB_REG_DATA = 0x00,
	ADB_REG_1,
	ADB_REG_2,
	ADB_REG_IDENT,
};

typedef union {

	struct {
		uint8_t reg : 2;
		uint8_t cmd : 2;
		uint8_t addr : 4;
	};

	uint8_t raw;
} adb_cmd_t;

typedef union {

	struct {
		uint16_t low : 2;
		uint16_t high : 2;
	};

	uint16_t raw;
} adb_evt_t;

void adb_init(void);

void adb_reset(void);

bool adb_recv(
	__inout adb_evt_t *evt
	);

void adb_send(
	__in adb_cmd_t *cmd,
	__in uint16_t *data
	);

#endif // ADB_H_
