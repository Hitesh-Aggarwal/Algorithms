OUT_DIR := ./out
MAIN_FILES := $(patsubst %.c, $(OUT_DIR)/%, $(wildcard *.c))
CFLAGS := -O3 -Wall

all: $(MAIN_FILES)

$(OUT_DIR)/radix_sort : radix_sort.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) -o $@ $< -lm

$(OUT_DIR)/protoVanEmdeBoasTree : protoVanEmdeBoasTree.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) -o $@ $< -lm

$(OUT_DIR)/vanEmdeBoasTrees : vanEmdeBoasTrees.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) -o $@ $< -lm

$(OUT_DIR)/% : %.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OUT_DIR)
