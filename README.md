PopStar AI
==========

The simple AI of the small app game "popstar".


## Install

```bash
./setup.sh
make
```


## Usage

`color2txt.py` is hardcode the position of image, which is only tested on iPhone SE screen shot.

```
./color2txt.py screen_shot.png | depth=4 ./popstar_ai_openmp -
```

### `popstar_ai`

argv[1] is text input file or `-` from `stdin`.


## TODO

1. Remember the best tree to avoid the re-search at the next stage
2. Add good heuristic function to prune the worse tree
3. Improve the data structure of maintaining the game state.
    * Need a good way to maintain the component in dynamicly.
    * Avoid cache miss
    * support multithread
4.Auto parse the image from different phone's screen-shot or a better way to get the game state.
