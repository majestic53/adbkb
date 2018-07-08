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

BIN=adbkb
CC=avr-gcc
CC_FLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(DEV)
DIR_BIN=./../bin/
DIR_BUILD=./../build/
DIR_SRC=./
LIB=libadbkb.a

all: adbkb

### BINARIES ###

adbkb:
	@echo ''
	@echo '--- BUILDING BINARY ------------------------'
	$(CC) $(CC_FLAGS) -c $(DIR_SRC)$(BIN).c -o $(DIR_BUILD)$(BIN).o
	$(CC) $(CC_FLAGS) -o $(DIR_BUILD)$(BIN).elf $(DIR_BUILD)$(BIN).o $(DIR_BUILD)$(LIB)
	avr-objcopy -j .text -j .data -O ihex $(DIR_BUILD)$(BIN).elf $(DIR_BIN)$(BIN).hex
	avr-size --format=avr --mcu=$(DEV) $(DIR_BUILD)$(BIN).elf
	@echo '--- DONE -----------------------------------'
	@echo ''
