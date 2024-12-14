# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes
TFLAGS = -lcheck -lsubunit -lm -pthread

# Files and target
SRCS = $(filter-out src/main.c, $(wildcard src/*.c))
OBJS = $(SRCS:.c=.o)
MAIN = src/main.c
TEST_SRCS = $(wildcard tests/test_*.c)

TARGET = db.bin
TARGET_TEST = ./build/test.bin


# Build target
all: $(TARGET)
$(TARGET): $(OBJS) $(MAIN:.c=.o)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MAIN:.c=.o)
	./$(TARGET)

 


# Run unit tests
test: $(OBJS)
	@mkdir -p build     
	@$(CC) $(CFLAGS) $(TEST_SRCS) $(OBJS) -o $(TARGET_TEST) $(TFLAGS)
	@$(TARGET_TEST)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET) src/main.o
	rm -rf build

.PHONY: all clean test
