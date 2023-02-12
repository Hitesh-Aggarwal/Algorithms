SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
CPPFLAGS := -O3 -Wall

run: main
	./main

main: $(OBJ_FILES)
	gcc -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	gcc $(CPPFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) main
