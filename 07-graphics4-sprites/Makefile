PROG = graphics4

GBDK_N = ../gbdk-n
CC = $(GBDK_N)/bin/gbdk-n-compile.sh
LD = $(GBDK_N)/bin/gbdk-n-link.sh
MR = $(GBDK_N)/bin/gbdk-n-make-rom.sh
IMG2GB = img2gb

_OBJ = $(patsubst %.c,%.rel,$(wildcard src/*.c))


all: build

build: $(PROG).gb

$(PROG).gb: $(_OBJ)
	$(LD) -o $(PROG).ihx $^
	$(MR) $(PROG).ihx $(PROG).gb

%.rel: %.c
	$(CC) -o $@ -c $<

assets:
	$(IMG2GB) tileset \
		--output-c-file=src/player.sprites.c \
		--output-header-file=src/player.sprites.h \
		--output-image=src/player.sprites.png \
		--alternative-palette \
		--sprite8x16 \
		--name PLAYER_SPRITES \
		./player.png

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
