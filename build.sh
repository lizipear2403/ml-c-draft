#!/bin/bash

set -xe
gcc multiLayer.c -o NN -lm -Wall -Wextra && ./NN
