PROG = graphics4
CC = GBDKDIR=./gbdk/build/ppc-unknown-linux2.2/gbdk/ ./gbdk/build/ppc-unknown-linux2.2/gbdk/bin/lcc
_OBJ = $(patsubst %.c,%.o,$(wildcard src/*.c))

all: build

run: build
	mednafen $(PROG).gb

build: $(PROG).gb

$(PROG).gb: $(_OBJ)
	$(CC) -Wl-m -o $(PROG).gb $^

src/%.o: src/%.c
	$(CC) -Wa-l -o $@ -c $<

sprites:
	img2gb tileset \
		--output-c-file=src/player.sprites.c \
		--output-header-file=src/player.sprites.h \
		--output-image=src/player.sprites.png \
		--alternative-palette \
		--sprite8x16 \
		--name PLAYER_SPRITES \
		./player.png

buildenv:
	git clone https://github.com/gheja/gbdk.git
	cd gbdk && make

clean:
	rm -rf src/*.o
	rm -rf src/*.lst
	rm -rf $(PROG).gb
	rm -rf $(PROG).map

