#!/bin/bash

set -xe
gcc NN.h NN.c  -o NN -lm -Wall  -Wextra && ./NN
