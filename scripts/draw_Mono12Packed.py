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

if (len(data) != SIZE_X * SIZE_Y * 1.5):
    print("wrong file size")
    exit(1)

image_array = np.empty((SIZE_Y, SIZE_X))


for (y, x) in np.ndindex(SIZE_Y, SIZE_X):
    start_bit = (y * SIZE_X + x) * 12
    idx_B = int(start_bit / 8)
    idx_b = start_bit % 8
    pixel_value = 0
    if (idx_b == 0):
        pixel_value |= data[idx_B] << 4
        pixel_value |= data[idx_B + 1] >> 4
    else:
        pixel_value |= data[idx_B + 1] << 4
        pixel_value |= data[idx_B] & 0xFF
    image_array[y, x] = pixel_value

cset1 = plt.imshow(image_array, cmap="rainbow")
plt.colorbar(cset1)

plt.tight_layout()
plt.show()
