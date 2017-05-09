#!/usr/bin/env python
import sys

from PIL import Image, ImageFilter

if len(sys.argv) > 1:
    path = sys.argv[1]
else:
    path = 'IMG_4987.PNG'


im = Image.open(path)
#print im.size

im = im.crop((0, 498, im.size[0], im.size[1]))
#im.save("test.bmp")

mp = []
for i in range(10):
    s = ''
    for j in range(10):
        xy = (64 * j + 32, 64 * i + 32)
        c = im.getpixel(xy)

        r, g, b = c

        if r > 150 and g > 150:
            c = 'y'
        elif b > 200 and g > 100:
            c = 'b'
        elif r > 200 and b > 150:
            c = 'p'
        elif r > 230 and b < 150:
            c = 'r'
        elif g > 200:
            c = 'g'
        else:
            assert False

        s += c
        #print c,
    mp.append(s)
    #print ''

print '\n'.join(mp)
