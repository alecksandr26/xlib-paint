C = cc
C_DEV_FLAGS = -ggdb -Wall -pedantic -Werror
C_COMPILE_FLAGS = -O2 -DNDEBUG -fno-stack-protector -z execstack -no-pie
C_FLAGS = $(C_DEV_FLAGS)
C_TEST_FLAGS = -ggdb  -Wall -pedantic -DTESTING_PAINT
C_TEST_LIB_FLAGS = -lunittest -ltc
C_LIB_FLAGS = -lX11 -lXft -I/usr/include/freetype2

AR = ar cr 

V = valgrind
V_FLAGS = --leak-check=full --track-origins=yes -s  --show-leak-kinds=all

CF = clang-format -i

PF = gprof
PF_FLAGS = --line --brief -B

M = makepkg
M_FLAGS = -f --config .makepkg.conf --skipinteg --noextract

SRC_DIR = src
INLCUDE_DIR = include
TEST_DIR = test
BUILD_DIR = build
PROGNAME = paint.out

MAIN = $(addprefix $(BUILD_DIR)/, $(PROGNAME))
OBJ_DIR = $(addprefix $(BUILD_DIR)/, obj)
LIB_DIR = $(addprefix $(BUILD_DIR)/, lib)

OBJS = $(addprefix $(OBJ_DIR)/, window.o graphics.o main.o colors.o tools.o canvas.o kbinds.o)
LIBS = $(addprefix $(LIB_DIR)/, libpaint.a)
TESTRUNNER = testrunner.out

.PHONY: all clean run test
all: $(BUILD_DIR) $(OBJ_DIR) $(OBJS) $(LIB_DIR) $(LIBS) $(MAIN) $(TESTRUNNER)

$(OBJ_DIR):
	mkdir -p $@

$(LIB_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(C) $(C_FLAGS) -c $< -o $@ $(C_LIB_FLAGS)

$(LIBS): $(filter-out obj/main.o, $(OBJS))
	$(AR) $@ $^

$(MAIN): $(OBJ_DIR)/main.o $(LIBS)
	$(C) $(C_FLAGS) $^ -o $@ $(C_LIB_FLAGS)

run: $(MAIN)
	$(V) $(V_FLAGS) ./$<

prof: $(MAIN)
	@echo Generate the gmon.out
	./$<
	@echo Profiling
	$(PF) $(PF_FLAGS) ./$<

$(TESTRUNNER): C_FLAGS = $(C_TEST_FLAGS)
$(TESTRUNNER): $(basename $(TESTRUNNER)).c $(LIBS)
	$(C) $(C_FALGS) $< -o $@ $(C_TEST_LIB_FLAGS)

test: $(TESTRUNNER)
	./$(TESTRUNNER)

clean:
ifneq ("$(wildcard $(OBJ_DIR)/*.o)", "")
	rm $(wildcard $(OBJ_DIR)/*.o)
endif

ifneq ("$(wildcard $(OBJ_DIR))", "")
	rmdir $(OBJ_DIR)
endif

ifneq ("$(wildcard $(MAIN))", "")
	rm $(MAIN)
endif

ifneq ("$(wildcard $(PROGNAME)*)", "")
	rm $(PROGNAME)*
endif

ifneq ("$(wildcard $(LIB_DIR)/*.a)", "")
	rm $(wildcard $(LIB_DIR)/*.a)
endif

ifneq ("$(wildcard $(LIB_DIR))", "")
	rmdir $(LIB_DIR)
endif

ifneq ("$(wildcard $(TESTRUNNER))", "")
	rm $(TESTRUNNER)
endif

clean-build:
ifneq ("$(wildcard $(BUILD_DIR))", "")
	rm -r $(BUILD_DIR)
endif

compile: C_FLAGS = $(C_COMPILE_FLAGS)
compile: clean $(BUILD_DIR) $(OBJ_DIR) $(OBJS) $(LIB_DIR) $(LIBS) $(MAIN)

pkg:
	$(M) $(M_FLAGS)	
