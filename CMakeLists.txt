cmake_minimum_required(VERSION 3.15)

project(CTetris VERSION 0.1
                DESCRIPTION "A version of tetris in C"
                LANGUAGES C)

add_executable(cTetris game.c game.h)
