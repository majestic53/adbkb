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

#include "../include/uart.h"
#define BAUD 9600
#include <util/setbaud.h>

void
uart_init(void)
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	BIT_SET_COND(USE_2X, UCSR0A, U2X0);

	UCSR0B = 0;
	BIT_SET(UCSR0B, TXEN0);

	UCSR0C = 0;
	BIT_SET(UCSR0C, UCSZ00);
	BIT_SET(UCSR0C, UCSZ01);
}

void
uart_send(
	__in uint8_t data
	)
{
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;
}
