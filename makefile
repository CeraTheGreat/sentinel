CC = gcc
CT = ctags

CFLAGS = -O2
DFLAGS = -g -Wall
LFLAGS = -lutil -lncurses

PROG_NAME = sentinel
SRC_DIR = ./src
BIN_DIR = ./bin
SRC_LIST = $(wildcard $(SRC_DIR)/*.c)
HED_LIST = $(wildcard $(SRC_DIR)/*.h)

.PHONY: all clean $(PROG_NAME) debug development

default: development

all: $(PROG_NAME)

$(PROG_NAME): $(SRC_LIST) $(HED_LIST)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_LIST) $(LFLAGS)
	rm .tags

debug: $(SRC_LIST) $(HED_LIST)
	$(CC) -DDEBUG $(DFLAGS) -o $(BIN_DIR)/$(PROG_NAME) $(SRC_LIST) $(LFLAGS)
	etags -o $(SRC_DIR)/.tags $(SRC_LIST) $(HED_LIST)

development: $(SRC_LIST) $(HED_LIST)
	$(CC) $(DFLAGS) -o $(BIN_DIR)/$(PROG_NAME) $(SRC_LIST) $(LFLAGS)
	etags -o $(SRC_DIR)/.tags $(SRC_LIST) $(HED_LIST)

clean:
	rm -f $(BIN_DIR)/$(PROG_NAME)
	rm $(SRC_DIR)/.tags

