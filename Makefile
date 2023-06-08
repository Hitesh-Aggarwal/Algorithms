OUT_DIR := ./out
LIBS := graph.c disjoint_sets.c priority_queue.c queue.c
MAIN_FILES := $(patsubst %.c, $(OUT_DIR)/%, $(filter-out $(LIBS), $(wildcard *.c)))
CFLAGS := -O3 -Wall

graph_files := breadth_first_search.c depth_first_search.c kruskal_algo.c strongly_connected_components.c bellman_ford.c dag_shortest_paths.c dijkastra.c prims_algorithm.c
GRAPH_FILES := $(patsubst %.c, $(OUT_DIR)/%, $(graph_files))

math_files := radix_sort.c protoVanEmdeBoasTree.c vanEmdeBoasTrees.c
MATH_FILES := $(patsubst %.c, $(OUT_DIR)/%, $(math_files))

all: $(MAIN_FILES)

$(OUT_DIR)/prims_algorithm : priority_queue.c
$(OUT_DIR)/kruskal_algo : disjoint_sets.c
$(OUT_DIR)/breadth_first_search : queue.c

$(MATH_FILES): -lm

$(GRAPH_FILES): graph.c

$(OUT_DIR)/% : %.c
	@mkdir -p $(@D)
	gcc $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OUT_DIR)
