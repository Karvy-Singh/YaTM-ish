#!/bin/bash
gcc -o main final.c parser.h parser.c resize.h resize.c -lSDL2 -lSDL2_image -lSDL2_ttf -lX11 && ./main
