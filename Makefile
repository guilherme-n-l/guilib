LDPATH = ./include
SRC_DIR = src
TMP_DIR = tmp 
TARGET_DIR = bin

PLAT := $(shell uname -s)

ifeq ($(PLAT), Darwin)
	CC = clang
	CFLAGS =
	LDFLAGS =
	LIBEXT = .dylib
else ifeq ($(PLAT), Linux)
	CC = gcc
	CFLAGS = 
	LDFLAGS = 
	LIBEXT = .so
endif

CFLAGS += -O3 -Wall -fPIC -I$(LDPATH)
LDFLAGS += -shared -L$(LDPATH)

SRC := $(wildcard $(SRC_DIR)/*.c)
# DEPS := $(patsubst $(SRC_DIR)/%.c, $(TMP_DIR)/%.d, $(SRC))

all: $(patsubst $(SRC_DIR)/%.c, $(TARGET_DIR)/lib%$(LIBEXT), $(SRC))

$(TARGET_DIR)/lib%$(LIBEXT): $(SRC)
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
