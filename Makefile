# Makefile

# Get user name.
USER = $(shell whoami)

# Include compiler tools.
include arm-none-eabi.mk

# Project paths.
LINKERSCRIPT := ldscript
SRC_DIR      := src
INCLUDE_DIR  := include
BUILD_DIR    := build
BIN_DIR      := bin

# Output file name.
TARGET = $(BIN_DIR)/blinky

# Component subdirectories.
PARTS_DIR  = $(SRC_DIR)/drivers
PARTS_DIR += $(SRC_DIR)/bsp

# Include path(s).
INCLUDES  = -I$(INCLUDE_DIR)
INCLUDES += -I$(SRC_DIR)/bsp
INCLUDES += -I$(SRC_DIR)/drivers

# Find all .c files.
SOURCES := $(shell find $(SRC_DIR) $(PART_DIR) -name '*.c')

# Generate object file paths.
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Auto-generated dependency files.
DEPS := $(OBJECTS:.o=.d)

# Phony targets.
.PHONY : all clean clobber flash

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
OPT    := -O0
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
TGT_CPPFLAGS += -MMD
TGT_CPPFLAGS += -MP
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

.SUFFIXES: .elf .bin .map
.SECONDEXPANSION:
.SECONDARY:

all : elf
elf : $(TARGET).elf
bin : $(TARGET).bin

$(TARGET).bin : $(TARGET).elf
	$(OBJCOPY) -Obinary $(*).elf $(*).bin

$(TARGET).elf : $(OBJECTS) $(LDSCRIPT)
	@mkdir -p $(BIN_DIR)
	$(CC) $(TGT_LDFLAGS) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $(TARGET).elf
	$(SIZE) $(TARGET).elf

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(TGT_CFLAGS) $(CFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

clean :
	@rm -rf $(BUILD_DIR)

clobber : clean
	@rm -rf $(BIN_DIR)

# Flash device.
flash : $(TARGET).bin
	@if [ -d "/media/$(USER)/FRDM-KL46Z" ]; then cp $(TARGET).bin /media/$(USER)/FRDM-KL46Z && sync; \
	else echo "The directory '/media/$(USER)/FRDM-KL46Z' does not exist."; fi

# What does this do?
-include $(DEPS)
