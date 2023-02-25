OUT_DIR := ./out
MAIN_FILES := $(patsubst %.c, $(OUT_DIR)/%.out, $(wildcard *.c))
CFLAGS := -O3 -Wall

all: $(MAIN_FILES)

$(OUT_DIR)/%.out : %.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OUT_DIR)
