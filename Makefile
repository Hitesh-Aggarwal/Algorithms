OUT_DIR := ./out
MAIN_FILES := $(patsubst %.c, $(OUT_DIR)/%, $(filter-out graph.c, $(wildcard *.c)))
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

$(OUT_DIR)/breadth_first_search : breadth_first_search.c graph.c

$(OUT_DIR)/depth_first_search : depth_first_search.c graph.c

$(OUT_DIR)/kruskal_algo : kruskal_algo.c graph.c

$(OUT_DIR)/prims_algorithm : prims_algorithm.c graph.c

$(OUT_DIR)/strongly_connected_components : strongly_connected_components.c graph.c

$(OUT_DIR)/bellman_ford: bellman_ford.c graph.c

$(OUT_DIR)/% : %.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OUT_DIR)
