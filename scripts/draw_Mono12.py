#!/usr/bin/env python3

import argparse
import numpy as np
import matplotlib.pyplot as plt
import sys
import os

SIZE_X = 2464
SIZE_Y = 2056

parser = argparse.ArgumentParser(description='draw image from camera')
parser.add_argument("filename", help="file name")
args = parser.parse_args()

with open(args.filename, 'rb') as f:
    data = f.read()

if (len(data) != SIZE_X * SIZE_Y * 2):
    print("wrong file size")
    exit(1)

image_array = np.empty((SIZE_Y, SIZE_X))

for (y, x) in np.ndindex(SIZE_Y, SIZE_X):
    idx = (y * SIZE_X + x) * 2
    pixel_data = data[idx:idx + 2]
    pixel_value = int.from_bytes(pixel_data, byteorder='little')
    image_array[y, x] = pixel_value

cset1 = plt.imshow(image_array, cmap="rainbow")
plt.colorbar(cset1)

plt.tight_layout()
plt.show()
