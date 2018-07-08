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

DEV_SRT=m328p

BIN=adbkb
BUILD_FLAGS_DBG=CC_BUILD_FLAGS=-g
BUILD_FLAGS_REL=CC_BUILD_FLAGS=-O3\ -DNDEBUG
DIR_BIN=./bin/
DIR_BUILD=./build/
DIR_LOG=./log/
DIR_ROOT=./
DIR_SRC=./src/
DIR_TOOL=./tool/
JOB_SLOTS=4
LOG_CLOC=cloc_stat.log

all: debug

debug: clean init lib_debug bin_debug

release: clean init lib_release bin_release

testing: debug test

statistics: clean init stat

clean:
	rm -rf $(DIR_BIN)
	rm -rf $(DIR_BUILD)
	rm -rf $(DIR_LOG)

### LIBRARIES ###

bin_debug:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING BINARIES (DEBUG)'
	@echo '============================================'
	cd $(DIR_TOOL) && make $(BUILD_FLAGS_DBG)

bin_release:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING BINARIES (RELEASE)'
	@echo '============================================'
	cd $(DIR_TOOL) && make $(BUILD_FLAGS_REL)

init:
	mkdir $(DIR_BIN)
	mkdir $(DIR_BUILD)
	mkdir $(DIR_LOG)

lib_debug:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING LIBRARIES (DEBUG)'
	@echo '============================================'
	cd $(DIR_SRC) && make $(BUILD_FLAGS_DBG) build -j $(JOB_SLOTS)
	cd $(DIR_SRC) && make archive

lib_release:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING LIBRARIES (RELEASE)'
	@echo '============================================'
	cd $(DIR_SRC) && make $(BUILD_FLAGS_REL) build -j $(JOB_SLOTS)
	cd $(DIR_SRC) && make archive

### FLASH ###

flash:
	@echo ""
	@echo "============================================"
	@echo "FLASHING SAMPLE"
	@echo "============================================"
	avrdude -p $(DEV_SRT) -P usb -c usbtiny -U flash:w:$(DIR_BIN)$(BIN).hex

### STATISTICS ###

stat: lines

lines:
	@echo ''
	@echo '============================================'
	@echo 'CALCULATING LINE COUNT'
	@echo '============================================'
	cloc $(DIR_ROOT) > $(DIR_LOG)$(LOG_CLOC)
