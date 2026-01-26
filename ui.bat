@echo off
clang ui.c -o ui `sdl2-config --cflags --libs`
./ui