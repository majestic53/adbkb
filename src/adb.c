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

#include <limits.h>
#include "../include/adb.h"

#define ADB_DDR DDRB
#define ADB_PORT PORTB
#define ADB_PIN PINB
#define ADB_PIN_BIT PB1

#define ADB_PIN_HIGH ADB_DDR &= ~_BV(ADB_PIN_BIT)
#define ADB_PIN_LOW ADB_DDR |= _BV(ADB_PIN_BIT)

#define ADB_DELAY_ATTEN 800
#define ADB_DELAY_BIT_0_HIGH 35
#define ADB_DELAY_BIT_0_LOW 65
#define ADB_DELAY_BIT_1_HIGH 65
#define ADB_DELAY_BIT_1_LOW 35
#define ADB_DELAY_RESET 200
#define ADB_DELAY_SYNC 70
#define ADB_DELAY_TLT 150

#define ADB_RECV_DELAY 5
#define ADB_RECV_LEN 18
#define ADB_RECV_TIMEOUT 250
#define ADB_RECV_TOL_HIGH 45
#define ADB_RECV_TOL_LOW 25

void
adb_send_0(void)
{
	ADB_PIN_LOW;
	_delay_us(ADB_DELAY_BIT_0_LOW);
	ADB_PIN_HIGH;
	_delay_us(ADB_DELAY_BIT_0_HIGH);
}

void
adb_send_1(void)
{
	ADB_PIN_LOW;
	_delay_us(ADB_DELAY_BIT_1_LOW);
	ADB_PIN_HIGH;
	_delay_us(ADB_DELAY_BIT_1_HIGH);
}

void
adb_init(void)
{
	ADB_PIN_HIGH;
	ADB_PORT &= ~_BV(ADB_PIN_BIT);
}

void
adb_reset(void)
{
	ADB_PIN_LOW;
	_delay_ms(ADB_DELAY_RESET);
	ADB_PIN_HIGH;
}

bool
adb_recv(
	__inout adb_evt_t *evt
	)
{
	bool res = true;
	uint8_t data[ADB_RECV_LEN] = { 0 };

	for(uint8_t iter = 0; iter < ADB_RECV_LEN; ++iter) {
		int cnt = 0;

		for(;;) {

			cnt += ADB_RECV_DELAY;
			if(cnt >= ADB_RECV_TIMEOUT) {
				res = false;
				goto exit;
			}

			if(!(ADB_PIN & _BV(ADB_PIN_BIT))) {
				break;
			}

			_delay_us(ADB_RECV_DELAY);
		}

		cnt = 0;

		for(;;) {

			cnt += ADB_RECV_DELAY;
			if(cnt >= ADB_RECV_TIMEOUT) {
				res = false;
				goto exit;
			}

			if(ADB_PIN & _BV(ADB_PIN_BIT)) {
				break;
			}

			_delay_us(ADB_RECV_DELAY);
		}

		data[iter] = cnt;
	}

	for(uint8_t iter = 1; iter < (ADB_RECV_LEN - 1); ++iter) {
		evt->raw <<= 1;
		evt->raw |= (((data[iter] > ADB_RECV_TOL_LOW) && (data[iter] < ADB_RECV_TOL_HIGH)) ? 1 : 0);
	}

exit:

	return res;
}

void
adb_send(
	__in adb_cmd_t *cmd,
	__in uint16_t *data
	)
{
	uint8_t cmd_val = cmd->raw;

	ADB_PIN_LOW;
	_delay_us(ADB_DELAY_ATTEN);
	ADB_PIN_HIGH;
	_delay_us(ADB_DELAY_SYNC);

	for(uint8_t iter = 0; iter < CHAR_BIT; ++iter) {
		(cmd_val & ((uint8_t) INT8_MAX + 1)) ? adb_send_1() : adb_send_0();
		cmd_val <<= 1;
	}

	adb_send_0();

	if(data) {
		uint16_t data_val = *data;

		_delay_us(ADB_DELAY_TLT);
		adb_send_1();

		for(uint8_t iter = 0; iter < (sizeof(uint16_t) * CHAR_BIT); ++iter) {
			(data_val & ((uint16_t) INT16_MAX + 1)) ? adb_send_1() : adb_send_0();
			data_val <<= 1;
		}

		adb_send_0();
	}
}
