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

.PHONY: default all clean run pretty

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(TARGET)

# Indent linux-kernel style, but 4 spaces instead of 8
pretty:
	-indent *.c *.h -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 
	-cli0 -d0 -di1 -nfc1 -i4 -ip0 -l80 -lp -npcs -nprs -npsl -sai
	-saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1

clean:
	-rm -f *.o
	-rm -f $(TARGET)

run:
	./$(TARGET)
