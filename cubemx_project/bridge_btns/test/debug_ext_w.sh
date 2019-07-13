#!/bin/sh
PATH=$PATH:~/software/ac6/system_workbench/plugins/fr.ac6.mcu.externaltools.arm-none.linux64_1.13.1.201703061524/tools/compiler/bin
ddd --debugger arm-none-eabi-gdb ./Debug/test.elf
