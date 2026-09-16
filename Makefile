CC ?= cc
CFLAGS ?= -std=c89 -Wall -Wextra -Werror -pedantic -Iinclude
AMIGA_CC ?= m68k-amigaos-gcc
AMIGA_CFLAGS ?= -m68000 -Os -Wall -Wextra -Iinclude
BUILD := build

.PHONY: all check qualify-m1 qualify-m2-host amiga clean

all: $(BUILD)/amigopher

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/amigopher: src/main.c src/gopher.c src/transport_stub.c include/amigopher/amigopher.h include/amigopher/gopher.h include/amigopher/transport.h | $(BUILD)
	$(CC) $(CFLAGS) -o $@ src/main.c src/gopher.c src/transport_stub.c

$(BUILD)/test_gopher: tests/test_gopher.c src/gopher.c include/amigopher/gopher.h | $(BUILD)
	$(CC) $(CFLAGS) -o $@ tests/test_gopher.c src/gopher.c

check: $(BUILD)/amigopher $(BUILD)/test_gopher
	$(BUILD)/test_gopher

qualify-m1: check
	@echo "AmiGopher M1 host qualification: PASS"

qualify-m2-host: check
	@echo "AmiGopher M2 host transport/interface qualification: PASS"
	@echo "Amiga bsdsocket runtime qualification: PENDING"

amiga: | $(BUILD)
	$(AMIGA_CC) $(AMIGA_CFLAGS) -o $(BUILD)/AmiGopher src/main.c src/gopher.c src/transport_amiga.c

clean:
	rm -rf $(BUILD)
