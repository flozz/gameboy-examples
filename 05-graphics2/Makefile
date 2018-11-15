PROG = graphics2
CC = GBDKDIR=./gbdk/build/ppc-unknown-linux2.2/gbdk/ ./gbdk/build/ppc-unknown-linux2.2/gbdk/bin/lcc
_OBJ = $(patsubst %.c,%.o,$(wildcard src/*.c))

all: build

run: build
	mednafen $(PROG).gb

tileset:
	img2gb \
		--deduplicate \
		--map \
		--name=TILESET \
		--header-file=src/tileset.h \
		img.png \
		src/tileset.c

build: $(PROG).gb

$(PROG).gb: $(_OBJ)
	$(CC) -o $(PROG).gb $^

src/%.o: src/%.c
	$(CC) -o $@ -c $<

buildenv:
	git clone https://github.com/gheja/gbdk.git
	cd gbdk && make

clean:
	rm -rf src/*.o
	rm -rf $(PROG).gb
