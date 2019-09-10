PROG = hello

GBDK_N = ../gbdk-n
CC = $(GBDK_N)/bin/gbdk-n-compile.sh
LD = $(GBDK_N)/bin/gbdk-n-link.sh
MR = $(GBDK_N)/bin/gbdk-n-make-rom.sh

_OBJ = $(patsubst %.c,%.rel,$(wildcard src/*.c))


all: build

build: $(PROG).gb

$(PROG).gb: $(_OBJ)
	$(LD) -o $(PROG).ihx $^
	$(MR) $(PROG).ihx $(PROG).gb

%.rel: %.c
	$(CC) -o $@ -c $<

.PHONY: gbdk-n
gbdk-n:
	cd $(GBDK_N) && make

clean:
	rm -rf src/*.rel
	rm -rf src/*.lst
	rm -rf src/*.sym
	rm -rf src/*.asm
	rm -rf $(PROG).gb
	rm -rf $(PROG).ihx
	rm -rf $(PROG).map
	rm -rf $(PROG).sym
	rm -rf $(PROG).noi
	rm -rf $(PROG).lk
