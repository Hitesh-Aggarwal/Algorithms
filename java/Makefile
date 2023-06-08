CLASSES_DIR := ./classes
JAVA_FILES := $(patsubst %.java, $(CLASSES_DIR)/%.class, $(wildcard *.java))

all: $(JAVA_FILES)

$(CLASSES_DIR)/%.class : %.java
	@mkdir -p $(@D)
	javac -d $(CLASSES_DIR) $<

clean:
	rm -rf $(CLASSES_DIR)
