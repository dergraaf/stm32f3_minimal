
# C Flags
CFLAGS = -std=c99

# C++ Flags
CXXFLAGS = -std=c++11 -fno-exceptions -fno-rtti

# C and C++ Flags
CCFLAGS  = -mcpu=cortex-m4 -mthumb -mthumb-interwork
CCFLAGS += -Os
CCFLAGS += -I.
CCFLAGS += -DSTM32F3XX -DF_CPU=72000000
CCFLAGS += -Wall -Wextra

# Linker Flags
LINKFLAGS  = -mcpu=cortex-m4 -mthumb
LINKFLAGS += -nostartfiles -L. -Tstm32f3xx_c.ld

# Assembler Flags
ASFLAGS  = -mcpu=cortex-m4 -mthumb -mthumb-interwork
ASFLAGS += -gdwarf-2
ASFLAGS += -xassembler-with-cpp

# All the following flags are optional but may be useful:
# Enable FPU
CCFLAGS += -mfloat-abi=softfp -mfpu=fpv4-sp-d16

# All constants are assumed to be float (32 bit) and not
# double (32 bit) by default and warn if a float value is implicit promoted
# to double. Doubles are emulated in software while floats can use the FPU.
CCFLAGS += -fsingle-precision-constant -Wdouble-promotion

# Enable the linker to discard unused functions
CCFLAGS   += -ffunction-sections -fdata-sections
LINKFLAGS += -Wl,--relax -Wl,--gc-sections

build: clean
	arm-none-eabi-gcc $(CFLAGS) $(CCFLAGS) -c -o delay.o   delay.sx
	arm-none-eabi-gcc $(CFLAGS) $(CCFLAGS) -c -o main.o    main.c
	arm-none-eabi-gcc $(CFLAGS) $(CCFLAGS) -c -o startup.o startup.c   
	
	arm-none-eabi-gcc $(LINKFLAGS) -o main.elf main.o delay.o startup.o

program: build
	openocd -f openocd.cfg

clean:
	$(RM) *.o
	$(RM) main.elf

.PHONY: build program clean
