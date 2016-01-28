.PHONY :clean all
CC=gcc
CFLAGS=-Wall -g 
BIN=mqunlink1 mqcreate1 mqgetattr mqsend  mqrecv
all:$(BIN)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ 
mqunlink1:mqunlink1.o
	$(CC) $(CFLAGS) $^ -o $@ -lrt
mqcreate1:mqcreate1.o
	$(CC) $(CFLAGS) $^ -o $@ -lrt
mqgetattr:mqgetattr.o
	$(CC) $(CFLAGS) $^ -o $@ -lrt
mqsend:mqsend.o
	$(CC) $(CFLAGS) $^ -o $@ -lrt
mqrecv:mqrecv.o
	$(CC) $(CFLAGS) $^ -o $@ -lrt
clean:
	rm -f $(BIN) *.o  


