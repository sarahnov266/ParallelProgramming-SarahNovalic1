CC = gcc
CFLAGS = -Wall -std=c99

TARGET = sum_test

SOURCES = main.c sum_algorithms.c

HEADERS = sum_algorithms.h

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete!"

run: $(TARGET)
	./$(TARGET)

test_quick: $(TARGET)
	@echo "Running quick test (2^20 to 2^24)..."
	@./$(TARGET) | grep -A 6 "2^2[0-4]"

rebuild: clean all

help:
	@echo "Available targets:"
	@echo "  make          - Build the program (default)"
	@echo "  make run      - Build and run with all test sizes"
	@echo "  make clean    - Remove compiled files"
	@echo "  make rebuild  - Clean and rebuild from scratch"
	@echo "  make help     - Show this help message"

.PHONY: all clean run test_quick rebuild help
