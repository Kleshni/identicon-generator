TARGET = identicon
OBJS = main.o

CFLAGS += -std=c99
LDLIBS += -lidenticon

ifdef DEBUG
	CFLAGS += -g3 -Wpedantic -Wall -Wextra
else
	LDFLAGS += -s
endif

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(TARGET) $(OBJS)
