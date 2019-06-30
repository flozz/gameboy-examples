PROG = graphics5
CC = GBDKDIR=./gbdk/build/ppc-unknown-linux2.2/gbdk/ ./gbdk/build/ppc-unknown-linux2.2/gbdk/bin/lcc
_OBJ = $(patsubst %.c,%.o,$(wildcard src/*.c))

all: build

run: build
	mednafen $(PROG).gb

build: $(PROG).gb

$(PROG).gb: $(_OBJ)
	$(CC) -o $(PROG).gb $^

src/%.o: src/%.c
	$(CC) -o $@ -c $<

tileset:
	img2gb tileset \
		--output-c-file=src/tileset.c \
		--output-header-file=src/tileset.h \
		--output-image=src/tileset.png \
		tileset.png

tilemap: tileset
	img2gb tilemap \
		--output-c-file=src/window_tilemap.c \
		--output-header-file=src/window_tilemap.h \
		--name WINDOW_TILEMAP \
		src/tileset.png \
		window_tilemap.png

buildenv:
	git clone https://github.com/gheja/gbdk.git
	cd gbdk && make

clean:
	rm -rf src/*.o
	rm -rf $(PROG).gb