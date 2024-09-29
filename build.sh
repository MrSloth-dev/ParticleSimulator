#!/bin/zsh


set -xe
clang main.c particles.c -O2 -lraylib -lm -o particle -g
