CC = cc
CFLAGS = -Wall -Wextra -Werror -Wpedantic

ifeq ($(shell uname -s), Linux)
	CFLAGS +=-fsanitize=leak
endif

ifdef FSAN
	CFLAGS +=-fsanitize=address
endif

ifdef BUG
	CFLAGS +=-g
endif

NAME = woody_woodpacker

SRC_DIR = srcs
PARSE_BIN_DIR = parse_binary

SRC :=	$(wildcard $(SRC_DIR)/*.c) \
		$(wildcard $(SRC_DIR)/$(PARSE_BIN_DIR)/*.c)

OBJS_DIR = objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

I_DIRS := $(shell find . -type f -name "*.h" -exec dirname {} + | uniq)
INCLUDE = $(I_DIRS:%=-I%)

all: $(NAME)
.PHONY: all

$(NAME): $(OBJS_DIR) $(OBJ)
	$(CC) $(C_FLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJ)
.PHONY: clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJS_DIR)
.PHONY: fclean

re: fclean all
.PHONY: re

fsan:
	$(MAKE) FSAN=1 BUG=1
.PHONY: fsan

resan:	fclean fsan
.PHONY: resan

debug:
	$(MAKE) BUG=1
.PHONY: debug

rebug:	fclean debug
.PHONY: rebug

# setpath:
# 	export PATH=$(shell pwd):$(PATH)
# .PHONY: setpath
