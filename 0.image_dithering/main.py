# -*- encoding: utf-8 -*-
from PIL import Image

imagePath = "test.png"
blackImagePath = "black.png"
colorImagePath = "color.png"

im = Image.open(imagePath).convert('L')
width, height = im.size

N = 4
Dither = [[ 0,  8,  2, 10],
          [12,  4, 14,  6],
          [ 3, 11,  1,  9],
          [15, 13,  7,  5]]

for w in range(0, width):
  for h in range(0, height):
    i = w % N
    j = h % N
    Input = im.getpixel((w, h)) // 16
    if Input > Dither[i][j]:
      Output = 255
    else:
      Output = 0
    im.putpixel((w,h), Output)


im.save(blackImagePath)

im = Image.open(imagePath)

for w in range(0, width):
  for h in range(0, height):
    i = w % N
    j = h % N
    Input = im.getpixel((w, h))
    Output = [0, 0, 0, 255]
    for x in range(0, 3):
      if Input[x] // 16 > Dither[i][j]:
        Output[x] = 255
      else:
        Output[x] = 0
      im.putpixel((w,h), tuple(Output))

im.save(colorImagePath)