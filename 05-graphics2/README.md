# GameBoy Example 05: Graphics 2

> Converts an image using [img2gb][] and display it

![Graphics 2](./graphics2-screenshot.png)

Related article (in French): https://blog.flozz.fr/2018/11/19/developpement-gameboy-5-creer-des-tilesets/

Instructions to build this example can be found in [the main README file of this repository](https://github.com/flozz/gameboy-examples/#compiling-examples).


## Image Conversion

In addition to the other build commands documented in the main README file of this repository, I added an other one to regenerate `src/tileset.c` and `src/tileset.h` from `img.png`:

    make tileset

Note that you need to install [img2gb][] to generate the tileset.


[img2gb]: https://github.com/flozz/img2gb
