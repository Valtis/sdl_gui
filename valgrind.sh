#!/bin/bash
valgrind --tool=memcheck --suppressions=./supression.supp --leak-check=yes ./sdl_gui
