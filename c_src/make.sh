#!/usr/bin/bash
clear
gcc -pipe \
    main.c blake2bmod.c -o rngcard \
    -Wall -Werror -Wfatal-errors \
    -O3 -flto -fomit-frame-pointer -march=native -mtune=native
echo -e -n "\n Completed compiling at " && date '+%-l:%M %P'