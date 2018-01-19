# Slo-mo action game

Top down action game, can slow the game down & replay the level at full speed

***

## Building dependencies

Most dependencies are built automatically, but some need to be installed on
your system before building the game.

### CEGUI
Download the CEGUI source [here](http://cegui.org.uk/). Build with the following:
```
mkdir build
cd build
cmake -DGLM_H_PATH=../../glm/ .. && make
```
or the equivalent on your platform. Then copy the cegui directory into deps/cegui.

## Building

When building on linux:
```
git submodule update --init --recursive
mkdir bin
cd bin
cmake ..
make
```

For other platforms / build systems (like `msbuild` or `ninja`) you can
generate different build files with the `-G` option on cmake. To see a list of
generators, run `cmake -G`.
