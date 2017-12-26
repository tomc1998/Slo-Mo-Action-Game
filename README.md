# Slo-mo action game

Top down action game, can slow the game down & replay the level at full speed

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
