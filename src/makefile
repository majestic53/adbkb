# ADB-Keyboard
# Copyright (C) 2018 David Jolly
#
# ADB-Keyboard is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ADB-Keyboard is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

F_CPU=8000000
DEV=atmega328p

CC=avr-gcc
CC_FLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(DEV)
DIR_BIN=./../bin/
DIR_BUILD=./../build/
DIR_INC=./../include/
DIR_SRC=./
LIB=libadbkb.a

all: build archive

archive:
	@echo ''
	@echo '--- BUILDING LIBRARY -----------------------'
	ar rcs $(DIR_BUILD)$(LIB) $(DIR_BUILD)base_adb.o $(DIR_BUILD)base_uart.o
	@echo '--- DONE -----------------------------------'
	@echo ''

build: build_base

### BASE ###

build_base: base_adb.o base_uart.o

base_adb.o: $(DIR_SRC)adb.c $(DIR_INC)adb.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC)adb.c -o $(DIR_BUILD)base_adb.o

base_uart.o: $(DIR_SRC)uart.c $(DIR_INC)uart.h
	$(CC) $(CC_FLAGS) $(CC_BUILD_FLAGS) $(CC_TRACE_FLAGS) -c $(DIR_SRC)uart.c -o $(DIR_BUILD)base_uart.o
