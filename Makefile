CC := clang++
CFLAGS := -std=c++14 -I dependencies -I headers -Wall -Werror
SOURCES := $(wildcard src/*.cpp)
EXAMPLE_SOURCE := $(wildcard example/*.cpp)
UNIT_SOURCE := tests/unit_tests.cpp
INTEGRATION_SOURCE := tests/integration_tests.cpp
UNIT_TEST_TARGET := bin/unit_test
INTEGRATION_TEST_TARGET := bin/integration_test
EXAMPLE_TARGET := bin/example_run

unit_tests: $(SOURCES) $(UNIT_SOURCE)
	$(CC) $(CFLAGS) $(SOURCES) $(UNIT_SOURCE) -o $(UNIT_TEST_TARGET)

integration_tests: $(SOURCES) $(INTEGRATION_SOURCE)
	$(CC) $(CFLAGS) $(SOURCES) $(INTEGRATION_SOURCE) -o $(INTEGRATION_TEST_TARGET)

example: $(SOURCES) $(EXAMPLE_SOURCE)
	$(CC) $(CFLAGS) $(SOURCES) $(EXAMPLE_SOURCE) -o $(EXAMPLE_TARGET)

run_example:
	$(EXAMPLE_TARGET)

run_tests:
	$(UNIT_TEST_TARGET) &
	$(INTEGRATION_TEST_TARGET)

.PHONY : clean
clean :
	-rm $(wildcard bin/*)
