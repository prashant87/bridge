#!/bin/sh
#PATH=$PATH:~/programs/code-sourcery/2011.03-42/bin
PATH=$PATH:~/programs/sw4stm32/plugins/fr.ac6.mcu.externaltools.arm-none.linux32_1.11.0.201610101318/tools/gcc-arm-none-eabi-5_4-2016q2/bin
#PATH=$PATH:~/programs/sw4stm32/plugins/fr.ac6.mcu.externaltools.arm-none.linux32_1.7.0.201602291259/tools/compiler/bin
ddd --eval-command "target remote :4242" --debugger arm-none-eabi-gdb ./Debug/bridge.elf
