#!/bin/bash

set -xe
gcc main.c -o NN -lm -Wall && ./NN
