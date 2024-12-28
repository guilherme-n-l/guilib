LDPATH = ./guilib/include
SRC_DIR = guilib/src
TMP_DIR = tmp 
TARGET_DIR = bin

CC = gcc
CFLAGS = -O3 -Wall -fPIC -I$(LDPATH)
LDFLAGS = -shared

SRC := $(wildcard $(SRC_DIR)/*.c)
DEPS := $(patsubst $(SRC_DIR)/%.c, $(TMP_DIR)/%.d, $(SRC))

all: $(patsubst $(SRC_DIR)/%.c, $(TARGET_DIR)/lib%.so, $(SRC))

$(TARGET_DIR)/lib%.so: $(SRC)
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
