ARDUINO_CLI ?= arduino-cli
SOURCES=$(wildcard src/algernon/*.cpp src/algernon/*.h src/algernon/*.ino)

ifdef DRONE_COMMIT
VERBOSE=-v
endif

build: output/algernon.ino.hex

output/algernon.ino.hex: src/algernon/gitrevs.h ${SOURCES}
	${ARDUINO_CLI} compile \
		--libraries lib \
		--build-path ${CURDIR}/build \
		--output-dir ${CURDIR}/output \
		${VERBOSE} \
		src/algernon

src/algernon/gitrevs.h.new: GIT_REV=$(shell git describe --tags --always --dirty)
src/algernon/gitrevs.h.new: KALEIDOSCOPE_GITREV=$(shell cd lib/hardware/keyboardio/avr/libraries/Kaleidoscope && git rev-parse --short HEAD)
src/algernon/gitrevs.h.new:
	echo "#define GIT_REV \"${GIT_REV}\"" >$@
	echo "#define KALEIDOSCOPE_GITREV \"${KALEIDOSCOPE_GITREV}\"" >>$@

src/algernon/gitrevs.h: src/algernon/gitrevs.h.new
	cmp -s $@ $^ || mv $^ $@
	rm -f $^

setup update link: tools/bootstrap.sh
	. tools/bootstrap.sh && $@

.PHONY: setup build update link
