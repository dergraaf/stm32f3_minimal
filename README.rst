Minimal C++ project for the STM32F3Discovery Board
==================================================

This is (almost) the bare minimum to get a blinking LED on a `STM32F3Discovery`_ board.

Works with the `ARM GCC toolchain`_ (arm-none-eabi-gcc (Linaro GCC 4.7-2013.01))

Three Step Guide::

   cd blink
   ./build.sh
   ./flash main.elf

Most headers are copied from CMSIS and STM's libs, startup is from xpcc_ (and sligthly modified).

.. _`STM32F3Discovery`: http://www.st.com/web/en/catalog/tools/FM116/SC959/SS1532/PF254044
.. _`ARM GCC toolchain`: https://launchpad.net/gcc-arm-embedded
.. _xpcc: https://github.com/roboterclubaachen/xpcc
