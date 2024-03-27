# Define the compiler
CC := $(CROSS_COMPILE)gcc

# Define any compile-time flags
CFLAGS=-Wall

# Define the target executable name
TARGET=writer

# Define the source files
SOURCES=writer.c

# Define the object files from the sources
OBJECTS=$(SOURCES:.c=.o)

# Rule for making the target
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Rule for compiling source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean the build
clean:
	rm -f $(TARGET) $(OBJECTS)
