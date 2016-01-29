.PHONY :clean all
CC=gcc
CFLAGS=-Wall -g
BIN=producer_consumer
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
producer_consumer:producer_consumer.o 
	$(CC) $(CFLAGS) $^ -o $@ -lpthread
clean:
	rm -f $(BIN) *.o

