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

#ifndef DEF_H_
#define DEF_H_

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#ifndef __in
#define __in
#endif // __in

#ifndef __inout
#define __inout
#endif // __inout

#define BIT_CHK(_R_, _B_) (((_R_) & _BV(_B_)) == _BV(_B_))
#define BIT_CLR(_R_, _B_) ((_R_) &= ~_BV(_B_))
#define BIT_SET(_R_, _B_) ((_R_) |= _BV(_B_))
#define BIT_SET_COND(_C_, _R_, _B_) ((_C_) ? BIT_SET(_R_, _B_) : BIT_CLR(_R_, _B_))

#endif // DEF_H_
