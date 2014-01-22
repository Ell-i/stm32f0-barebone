CROSS = arm-none-eabi-
CPU = -mthumb -mcpu=cortex-m0
FPU = # -mfloat-abi=soft

CFLAGS+= -std=c99 -Wall
CFLAGS+= -Os -ffunction-sections -fdata-sections -fno-builtin -ffreestanding

CC = ${CROSS}gcc
LD = ${CROSS}ld
OBJCOPY = ${CROSS}objcopy
SIZE = ${CROSS}size

# use these on the $(LD) line, as needed:
LIBM = ${shell ${CC} ${CFLAGS} --print-file-name=libm.a}
LIBC = ${shell ${CC} ${CFLAGS} --print-file-name=libc.a}
LIBGCC = ${shell ${CC} ${CFLAGS} --print-libgcc-file-name}

CFLAGS += $(CPU) $(FPU)
LDFLAGS += --gc-sections

CFLAGS += -DCORE_M0PLUS -ICMSIS/Include -ICMSIS/Device/ST/STM32F0xx/Include/ -ISTM32F0xx_StdPeriph_Driver -ISTM32F0xx_StdPeriph_Driver/inc -include stm32f0xx_conf.h
CHIP_OBJS = $(patsubst %.c,%.o,$(wildcard STM32F0xx_StdPeriph_Driver/src/*.c)) \
            $(patsubst %.c,%.o,$(wildcard CMSIS/Device/ST/STM32F0xx/Source/Templates/*.c)) \
            $(patsubst %.c,%.o,$(wildcard gcc_stm32f0_lib/*.c)) 
LINKERSCRIPT = gcc_stm32f0_lib/gcc_stm32f0.ld

.PHONY: all clean

all: simple_test.bin

clean:
	-rm STM32F0xx_StdPeriph_Driver/src/*.o ./CMSIS/Device/ST/STM32F0xx/Source/Templates/*.o gcc_stm32f0_lib/*.o *.o *.axf *.bin

simple_test.axf: $(CHIP_OBJS) simple_test.o
	$(LD) -o $@ $(LDFLAGS) -T $(LINKERSCRIPT) $^ $(LIBGCC)

%.bin: %.axf
	$(OBJCOPY) --strip-unneeded -O binary $< $@
