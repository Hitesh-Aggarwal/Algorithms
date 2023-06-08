OUT_DIR := ./out
MAIN_FILES := $(patsubst %.c, $(OUT_DIR)/%, $(filter-out graph.c, $(wildcard *.c)))
CFLAGS := -O3 -Wall

graph_files := breadth_first_search.c depth_first_search.c kruskal_algo.c prims_algorithm.c strongly_connected_components.c bellman_ford.c
GRAPH_FILES := $(patsubst %.c, $(OUT_DIR)/%, $(graph_files))

math_files := radix_sort.c protoVanEmdeBoasTree.c vanEmdeBoasTrees.c
MATH_FILES := $(patsubst %.c, $(OUT_DIR)/%, $(math_files))

all: $(MAIN_FILES)

$(MATH_FILES): -lm

$(GRAPH_FILES): graph.c

$(OUT_DIR)/% : %.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OUT_DIR)
