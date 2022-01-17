CC = gcc
CFLAGS = -g -Wall -std=c99 -c
LDFLAGS = -g -Wall

BUILD_DIR = ./build

# A phony target is one that is not really the name of a file;
# rather it is just a name for a recipe to be executed when you make an explicit request.
# You can read more about them here: https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY : all test clean

all : philphix

philphix : philphix.o hashtable.o unittest.o
	$(CC) $(LDFLAGS) -o philphix $(BUILD_DIR)/philphix.o $(BUILD_DIR)/hashtable.o $(BUILD_DIR)/unittest.o 

philphix.o : src/philphix.c src/philphix.h src/hashtable.h build_dir
	$(CC) $(CFLAGS) src/philphix.c -o $(BUILD_DIR)/philphix.o

hashtable.o : src/hashtable.c src/hashtable.h build_dir
	$(CC) $(CFLAGS) src/hashtable.c -o $(BUILD_DIR)/hashtable.o

unittest.o : src/unittest.c src/unittest.h build_dir
	$(CC) $(CFLAGS) src/unittest.c -o $(BUILD_DIR)/unittest.o

build_dir :
	mkdir -p $(BUILD_DIR)

clean :
	rm -f $(BUILD_DIR)/*.o philphix tests/sanity/testOutput

# Make sure you leave testpassedall as the last thing in this line. You can add your own custom tests before it.
test: unittest testBasic testLongWords testFragmemts testIntegrated testpassedall # testEdge not applicable on windows

unittest: clean philphix
	@echo "================Running Unittest...================="
	./philphix
	@echo "=============All Unittests Completed================="
	@echo

testBasic: philphix
	touch tests/sanity/testOutput
	rm tests/sanity/testOutput
	@echo "================Running Program...================="
	cat tests/sanity/test | ./philphix tests/sanity/replace > tests/sanity/testOutput
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/sanity/testOutput tests/sanity/reference
	@echo "-----------------------None!-----------------------"
	@echo

testEdge: philphix
	@echo "Making the test files!"
	@echo
	@echo "A A" > null.txt
	@echo "================Running Program...================="
	cat philphix | ./philphix null.txt > newphilphix
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff philphix newphilphix
	@echo "-----------------------None!-----------------------"
	@rm -f null.txt newphilphix
	@echo

testLongWords: philphix
	@echo "Making the test files!"
	@echo "================Running Program...================="
	cat tests/longWords/test | ./philphix tests/longWords/replace > tests/longWords/testOutput
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/longWords/testOutput tests/longWords/reference
	@echo "-----------------------None!-----------------------"
	@echo

testFragmemts: philphix
	@echo "Making the test files!"
	@echo "================Running Program...================="
	cat tests/fragments/test | ./philphix tests/fragments/replace > tests/fragments/testOutput
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/fragments/testOutput tests/fragments/reference
	@echo "-----------------------None!-----------------------"
	@echo

testIntegrated: philphix
	@echo "Making the test files!"
	@echo "================Running Program...================="
	cat tests/integrated/test | ./philphix tests/integrated/replace > tests/integrated/testOutput
	@echo "================Program Finished!=================="
	@echo ""
	@echo "Difference between test output and reference output"
	@echo "---------------------------------------------------"
	@diff tests/integrated/testOutput tests/integrated/reference
	@echo "-----------------------None!-----------------------"
	@echo

testpassedall:
	@echo "You have passed all of the tests!"
