CC := gcc
CFLAGS = -Wunused-but-set-variable -Wreturn-type
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c,%.o,$(SOURCES))

install: final	
	mkdir bin
	mv final bin/final

all: final

final: $(OBJECTS)
	$(CC) $(CFLAGS)  $^ -o $@  

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $^ 

clean: 
	rm $(OBJECTS) 
	rm -dir -f bin

depend: $(SOURCES) 
	$(CC) $(CFLAGS)  -MM $^ >| $@

-include depend