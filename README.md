PopStar AI
==========

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

