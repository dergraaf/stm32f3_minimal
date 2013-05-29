Minimal C/C++ project for the STM32F3Discovery Board
====================================================

This is (almost) the bare minimum to get a blinking LED on a
`STM32F3Discovery`_ board.

Works with the `ARM GCC toolchain`_ (arm-none-eabi-gcc (Linaro GCC 4.7-2013.01))

Three Step Guide::

   cd blink
   make build
   make program

The Makefile is only used as a grouping mechanism for the different commands.
It doesn't contain any dependency logic for the build.

Most headers are copied from CMSIS and STM's libs, startup is from xpcc_
(and sligthly modified).

Additional Resources:

- `STM32F303VC Product Page <http://www.st.com/web/catalog/mmc/FM141/SC1169/SS1576/LN1531/PF252054>`_
- `STM32F303xC Datasheet <http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00058181.pdf>`_
- `STM32F3 Family Reference Manual <http://www.st.com/st-web-ui/static/active/en/resource/technical/document/reference_manual/DM00043574.pdf>`_
- `Cortex-M4 Technical Reference Manual <http://infocenter.arm.com/help/topic/com.arm.doc.ddi0439c/DDI0439C_cortex_m4_r0p1_trm.pdf>`_

.. _`STM32F3Discovery`: http://www.st.com/web/en/catalog/tools/FM116/SC959/SS1532/PF254044
.. _`ARM GCC toolchain`: https://launchpad.net/gcc-arm-embedded
.. _xpcc: https://github.com/roboterclubaachen/xpcc
