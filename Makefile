# **************************************************************************** #
#                                                                              #
#                                                 __ ______ ______ _______     #
#    Makefile                                    _██ ██████ ██████ ███████     #
#                                                ███  ____█  ____█     _██     #
#    By: aallali <hi@allali.me>                   ██  █████  █████    _██      #
#                                                 ██ _____█ _____█   _██       #
#    Created: 2024/12/13 13:37:42 by aallali      ██ ██████ ██████   ██.ma     #
#    Updated: 2024/12/16 15:58:51 by aallali      -------- 1337.ma -------     #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes
VALGRING_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes -s
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

run: $(TARGET)
	./$(TARGET)

cleanObjects:
	rm -f $(OBJS)
	
test: $(OBJS)
	@mkdir -p build     
	@$(CC) $(CFLAGS) $(TEST_SRCS) $(OBJS) -o $(TARGET_TEST) $(TFLAGS)
	@rm src/*.o
	@$(TARGET_TEST) --unittest

leak: $(TARGET)
	valgrind $(VALGRING_FLAGS) ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) src/main.o
	rm -rf build

.PHONY: all clean test
