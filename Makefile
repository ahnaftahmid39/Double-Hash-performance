CC=g++
BIN=bin
TEST=test
OUTPUT=output
DATASET_SIZE=10000
SEARCHSET_SIZE=3000

all: output_folder dataset main
	$(BIN)/dataset > dataset.txt && $(BIN)/main < dataset.txt > result.txt

allclean: clean all

main: main.cpp
	$(CC) -D dataset_size=$(DATASET_SIZE) -D searchset_size=$(SEARCHSET_SIZE) -o $(BIN)/$@ $^
dataset: dataset.cpp
	$(CC) -D dataset_size=$(DATASET_SIZE) -D searchset_size=$(SEARCHSET_SIZE) -o $(BIN)/$@ $^

test.out: test.cpp
	$(CC) -D dataset_size=$(DATASET_SIZE) -D searchset_size=$(SEARCHSET_SIZE) -o $(TEST)/$@ $^

run_test: test_folder dataset test.out
	$(BIN)/dataset > $(TEST)/dataset_test.txt && $(TEST)/test.out < $(TEST)/dataset_test.txt > $(TEST)/output_test.txt

output_folder:
	mkdir -p $(BIN)

test_folder:
	mkdir -p $(TEST)

clean:
	rm -f $(BIN)/* dataset.txt result.txt