src = $(wildcard src/*.c)
obj = $(src:.c=.o)

CFLAGS = -Ofast -march=native -mtune=native -s -Iinclude
LDFLAGS = -lm 

longstocking: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) longstocking
