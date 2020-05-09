BUILD_DIR=Build
SRC_DIR=Src
INC_DIR=Inc
CC=avr-gcc
LD=ld
LIBS=
STANDART=c99
OPTIMIZE=-Og
TARGET=main

C_SOURCES= \
$(SRC_DIR)/main.c

C_INCLUDES= \
-I$(INC_DIR)/

C_DEFS=

CFLAGS=$(C_DEFS) $(C_INCLUDES) $(OPTIMIZE) --std=$(STANDART) -Wno-write-strings -Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wlogical-op -Wredundant-decls -Wsign-conversion -Werror -IInclude -Wall -Wextra -Wpedantic -pedantic-errors 
LFLAGS=-Wall -Wextra -lm $(LIBS)

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

TOBJECTS = $(filter-out $(BUILD_DIR)/$(TARGET).o,$(OBJECTS))


all: $(TARGET) Dir

$(TARGET): $(OBJECTS) Makefile
	@echo -e '\033[1;32mCC\t'$(OBJECTS)' '$@'\033[0m'
	@$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo -e '\033[1;32mCC\t'$<'\033[0m'
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@


BuildDir:
	@mkdir -p $(BUILD_DIR)

SrcDir:
	@mkdir -p $(SRC_DIR)

IncDir:
	@mkdir -p $(INC_DIR)

Dir: BuildDir SrcDir IncDir



clean:
	@rm -rf $(BUILD_DIR)/*
	@echo -e '\033[0;31mCleaned\033[0m'

