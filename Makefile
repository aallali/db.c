# **************************************************************************** #
#    Copyright 2024 <Abdellah ALLALI>                                          #
#                                                                              #
#    File    : Makefile                                                        #
#    Project : DB.c                                                            #
#    License : Apache 2.0 with Commons Clause. See LICENSE file.               #
#                                                                              #
#    Created: 2024/12/13 13:37:42 by Abdellah A.                               #
#    Updated: 2024/12/31 13:00:42 by Abdellah A.                               #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes
VALGRING_FLAGS = --leak-check=full \
				 --show-leak-kinds=all \
				 --track-origins=yes \
				 -s
TFLAGS = -DUNIT_TEST

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
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(MAIN:.c=.o)
	@rm -f $(OBJS) src/main.o

run: $(TARGET)
	./$(TARGET) $(ARGS)
 
run-unsafe:
	$(MAKE) CFLAGS="-g -Iincludes" all
	./$(TARGET) $(ARGS)
	
test: $(OBJS)
	@mkdir -p build     
	$(CC) $(CFLAGS) $(TEST_SRCS) $(OBJS) -o $(TARGET_TEST) $(TFLAGS)
	@rm src/*.o
	valgrind $(VALGRING_FLAGS) $(TARGET_TEST) --unittest

test-single: $(OBJS)
	@mkdir -p build     
	@$(CC) $(CFLAGS) tests/test_main.c $(FILE) $(OBJS) -o $(TARGET_TEST) $(TFLAGS)
	@rm src/*.o
	valgrind $(VALGRING_FLAGS) $(TARGET_TEST) --unittest

leak: $(TARGET)
	valgrind $(VALGRING_FLAGS) ./$(TARGET) $(ARGS)

clean:
	rm -f $(OBJS) $(TARGET) src/main.o
	rm -rf build
