PROJECT=Project_C
SOURCES = $(wildcard *.c) $(wildcard */*.c)
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
LDFLAGS = -lm
CFLAGS = -g \
		   -std=c11 \
		   -MD \
		   -I. \
		   -Wall \
		   -Wextra \
		   -Werror \
		   -fsanitize=address \
		   -fsanitize=undefined 
 
$(PROJECT).out: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean test

all: $(PROJECT).out

clean:
	rm -f $(OBJECTS) $(SOURCES:.c=.d) $(PROJECT).out

test: $(PROJECT).out
	./$(PROJECT).out

-include $(SOURCES:.c=.d)
