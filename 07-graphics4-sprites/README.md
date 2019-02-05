# GameBoy Example 07: Graphics 4 - sprites

> A complete sprite example with an animated player

![Graphics 4](./graphics4-screenshot.gif)

Related article (in French): TODO

Instructions to build this example can be found in [the main README file of this repository](https://github.com/flozz/gameboy-examples/#compiling-examples).


## Image Conversion

In addition to the other build commands documented in the main README file of this repository, I added an other one to regenerate `src/player.sprites.c`, `src/player.sprites.h` and `src/player.sprites.png` from `player.png`:

    make sprites

Note that you need to install [img2gb][] >= 1.0.0 to generate the sprites.


[img2gb]: https://github.com/flozz/img2gb
