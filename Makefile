# Makefile

# Include compiler tools.
include arm-none-eabi.mk

# Output file name.
BINARY = blinky

# Include path(s).
LINKERSCRIPT := ldscript
SRC          := src

# Source files.
SRCFILES  = ${SRC}/startup.c
SRCFILES += ${SRC}/main.c

# Object file(s) to build.
TEMP1 = $(patsubst %.c,%.o,$(SRCFILES))
TEMP2 = $(patsubst %.cpp,%.o,$(TEMP1))
OBJS  = $(patsubst %.asm,%.o,$(TEMP2))

# Define linker script.
LDSCRIPT = $(LINKERSCRIPT)/kl46z256vxx4.ld

# Architecture (chip) specific flags.
ARCH_FLAGS  = -mcpu=cortex-m0plus
ARCH_FLAGS += -mthumb
ARCH_FLAGS += -msoft-float

# Assembler flags.
ASFLAGS  = -mthumb
ASFLAGS += -mcpu=cortex-m0plus

# Common flags.
OPT    := -Os
DEBUG  := -g
CSTD   ?= -std=c99
CXXSTD ?= -std=c++11

# Target C flags.
TGT_CFLAGS += $(OPT) $(DEBUG) $(CSTD)
TGT_CFLAGS += $(ARCH_FLAGS)
TGT_CFLAGS += -specs=nano.specs
TGT_CFLAGS += -Wimplicit-function-declaration
TGT_CFLAGS += -Wredundant-decls
TGT_CFLAGS += -Wmissing-prototypes
TGT_CFLAGS += -Wstrict-prototypes

# Target C++ flags.
TGT_CXXFLAGS += $(OPT) $(DEBUG) $(CXXSTD)
TGT_CXXFLAGS += $(ARCH_FLAGS)
TGT_CXXFLAGS +=  -Weffc++

# C/C++ preprocessor common flags.
TGT_CPPFLAGS += -MD
TGT_CPPFLAGS += -Wall
TGT_CPPFLAGS += -Wundef
TGT_CPPFLAGS += -fno-common
TGT_CPPFLAGS += -ffunction-sections
TGT_CPPFLAGS += -fdata-sections
TGT_CPPFLAGS += -Wextra
TGT_CPPFLAGS += -Wshadow
TGT_CPPFLAGS += -Wredundant-decls
TGT_CPPFLAGS += -I.
TGT_CPPFLAGS += -I./${SRC}
TGT_CPPFLAGS += -I./include

# Linker flags.
TGT_LDFLAGS += --static
TGT_LDFLAGS += -nostartfiles
TGT_LDFLAGS += -T$(LDSCRIPT)
TGT_LDFLAGS += $(ARCH_FLAGS)
TGT_LDFLAGS += $(DEBUG)
TGT_LDFLAGS += -Wl,-Map=$(*).map
TGT_LDFLAGS += -Wl,--cref
TGT_LDFLAGS += -Wl,--gc-sections

# Used libraries.
LDLIBS += -specs=nosys.specs
LDLIBS += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

.SUFFIXES: .elf .bin .hex .srec .list .map
.SECONDEXPANSION:
.SECONDARY:

all : elf
elf  : $(BINARY).elf
bin  : $(BINARY).bin
hex  : $(BINARY).hex
srec : $(BINARY).srec
list : $(BINARY).list

%.bin : %.elf
	$(OBJCOPY) -O binary $(*).elf $(*).bin

%.hex : %.elf
	$(OBJCOPY) -O ihex $(*).elf $(*).hex

%.srec : %.elf
	$(OBJCOPY) -O srec $(*).elf $(*).srec

%.list : %.elf
	$(OBJCOPY) -S $(*).elf $(*).list

%.elf %.map : $(OBJS) $(LDSCRIPT)
	$(CC) $(TGT_LDFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(*).elf
	$(SIZE) $(BINARY).elf

%.o : %.c
	$(CC) $(TGT_CFLAGS) $(CFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(*).o -c $(*).c

%.o : %.cxx
	$(CXX) $(TGT_CXXFLAGS) $(CXXFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(*).o -c $(*).cxx

%.o : %.cpp
	$(CXX) $(TGT_CXXFLAGS) $(CXXFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(*).o -c $(*).cpp

%.o : %.asm
	$(AS) $(ASFLAGS) -o $*.o -c $<

clean :
	$(RM) *.o *.d generated.* $(OBJS) $(patsubst %.o,%.d,$(OBJS))

clobber : clean
	$(RM) -f *.elf *.bin *.hex *srec *.list *.map

# Flash device.
flash : $(BINARY).bin
	cp $(BINARY).bin /media/willy/FRDM-KL46Z && sync

.PHONY : clean elf bin hex srec list all

# What does this do?
-include $(OBJS:.o=.d)
