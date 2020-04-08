
EXECUTABLE= Brick

CC= gcc

CFLAGS= -c  

all:Bricks

INCLUDE = ./include

OUTPUT = ./Build

ROOT_DIR = .
ROOT_DIR_OBJ = $(patsubst $(ROOT_DIR)/%.c,$(ROOT_DIR)/%.o,$(wildcard $(ROOT_DIR)/*.c))

CORE_DIR = ./core
CORE_DIR_OBJ = $(patsubst $(CORE_DIR)/%.c,$(CORE_DIR)/%.o,$(wildcard $(CORE_DIR)/*.c))

Bricks:MAKEDIR $(ROOT_DIR_OBJ) $(CORE_DIR_OBJ) Brick_sys.o
	$(CC) $(OUTPUT)/*.o $(OUTPUT)/core/*.o -o $(OUTPUT)/$(EXECUTABLE)

MAKEDIR:
	mkdir -p Build/core

$(CORE_DIR)/%.o: $(CORE_DIR)/%.c
	$(CC) -I $(INCLUDE) -c $< -o $(OUTPUT)/$@  

Brick_sys.o: $(wildcard ./system/*.c)
	$(CC) -I $(INCLUDE) -c $^ -o $(OUTPUT)/$@

$(ROOT_DIR)/%.o: $(ROOT_DIR)/%.c
	$(CC) -I $(INCLUDE) -c $< -o $(OUTPUT)/$@ 

clean:
	rm -rf $(OUTPUT)



