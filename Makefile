C = cc
C_FLAGS = -ggdb -Wall -pedantic -Werror
LIB_FLAGS = -lX11 -lXft  -I/usr/include/freetype2

V = valgrind
V_FLAGS = --leak-check=full --track-origins=yes -s  --show-leak-kinds=all

SRC_DIR = src
INLCUDE_DIR = include
OBJ_DIR = obj
MAIN = main

OBJS = $(addprefix $(OBJ_DIR)/, window.o graphics.o main.o colors.o)

.PHONY: all clean run
all: $(OBJ_DIR) $(OBJS) $(MAIN)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(C) $(C_FLAGS) -c $< -o $@ $(LIB_FLAGS)

$(MAIN): $(OBJS) 
	$(C) $(C_FLAGS) $^ -o $@ $(LIB_FLAGS)

run: $(MAIN)
	$(V) $(V_FLAGS) ./$<

clean:
	rm -r $(OBJ_DIR)
	rm $(MAIN)
