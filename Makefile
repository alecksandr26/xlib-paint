C = cc
C_DEV_FLAGS = -ggdb -Wall -pedantic -Werror
C_COMPILE_FLAGS = -O2 -DNDEBUG -fno-stack-protector -z execstack -no-pie
C_FLAGS = $(C_DEV_FLAGS)
C_TEST_FLAGS = -ggdb  -Wall -pedantic
C_LIB_FLAGS = -lX11 -lXft -I/usr/include/freetype2

V = valgrind
V_FLAGS = --leak-check=full --track-origins=yes -s  --show-leak-kinds=all

CF = clang-format -i

PF = gprof

M = makepkg
M_FLAGS = -f --config .makepkg.conf --skipinteg --noextract

SRC_DIR = src
INLCUDE_DIR = include
OBJ_DIR = obj
TEST_DIR = test
BIN_DIR = bin
TEST_BIN_DIR = $(addprefix $(TEST_DIR)/, bin)
MAIN = $(addprefix $(BIN_DIR)/, main)

OBJS = $(addprefix $(OBJ_DIR)/, window.o graphics.o main.o colors.o tools.o canvas.o kbinds.o)
TESTS = $(addprefix $(TEST_BIN_DIR)/, 	test_open_display.out \
					test_canvas_init.out \
					test_create_window.out\
					test_load_graphics.out)

.PHONY: all clean run
all: $(OBJ_DIR) $(OBJS) $(BIN_DIR) $(MAIN) $(TEST_BIN_DIR) $(TESTS)

$(OBJ_DIR):
	mkdir -p $@

$(TEST_BIN_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(C) $(C_FLAGS) -c $< -o $@ $(C_LIB_FLAGS)

$(MAIN): $(OBJS) 
	$(C) $(C_FLAGS) $^ -o $@ $(C_LIB_FLAGS)

run: $(MAIN)
	$(V) $(V_FLAGS) ./$<

prof: $(MAIN)
	@echo Generate the gmon.out
	./$<
	@echo Profiling
	$(PF) ./$<

$(TEST_BIN_DIR)/%.out: $(TEST_DIR)/%.c $(OBJS)
	$(C) $(C_TEST_FLAGS) $(filter-out $(OBJ_DIR)/main.o, $^) -o $@ $(C_LIB_FLAGS)

%.out: $(TEST_BIN_DIR)/%.out
	$(V) $(V_FLAGS) ./$<

test: $(notdir $(TESTS))

clean:
ifneq ("$(wildcard $(OBJ_DIR)/*.o)", "")
	rm -r $(wildcard $(OBJ_DIR)/*.o)
endif

ifneq ("$(wildcard $(OBJ_DIR))", "")
	rmdir $(OBJ_DIR)
endif

ifneq ("$(wildcard $(MAIN))", "")
	rm -r $(MAIN)
endif

ifneq ("$(wildcard $(BIN_DIR))", "")
	rmdir $(BIN_DIR)
endif

compile: C_FLAGS = $(C_COMPILE_FLAGS)
compile: clean $(OBJ_DIR) $(OBJS) $(BIN_DIR) $(MAIN)

pkg:
	@$(M) $(M_FLAGS)	
