#
# IMPORTANT: 
# if you are modifying make rules use TABS not spaces
# any indents need to be TAB characters
# in vim press Ctrl-v <tab>
# in emacs press C-q <tab>
# otherwise you will have ninja bugs
#

TARGET = ezsh
CC = gcc -std=c99
CFLAGS = -g -Wall

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

.PHONY: default all clean run

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(TARGET)


clean:
	-rm -f *.o
	-rm -f $(TARGET)

run:
	./$(TARGET)
