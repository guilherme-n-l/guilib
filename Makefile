PLAT := $(shell uname -s)
S_DIR := src
T_DIR := bin
SRC := $(wildcard $(S_DIR)/*.c)
DEPS := $(S_DIR)/utils.c
LDPATH := ./include
CFLAGS := -O3 -Wall -fPIC -I$(LDPATH)
LDFLAGS := -shared

ifeq ($(PLAT), Darwin)
	CC = clang
	EXT = dylib
else ifeq ($(PLAT), Linux)
	CC = gcc
	EXT = so
endif

all: $(foreach f, $(SRC), lib$(basename $(notdir $(f))).$(EXT))

lib%.$(EXT): $(S_DIR)/%.c
	@if [[ ! $* = "utils" ]]; then \
		[[ ! -d $(T_DIR) ]] && mkdir $(T_DIR) ;\
		command="$(CC) $(CFLAGS) $(LDFLAGS) -o $(T_DIR)/lib$*.$(EXT) $(DEPS) $(S_DIR)/$*.c" ;\
		echo $${command} ;\
		eval $${command} ;\
	fi; \
