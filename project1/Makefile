TARGET = server client
GCC = gcc
CFLAGS = -std=c99 -g

SERVER_OBJ=server.o
CLIENT_OBJ=client.o
LIB=-lm -lbsm
.PHONY:clean

all: $(TARGET)

%.o: %.c
	@echo "making: " $@
	@$(GCC) $< -c $(CFLAG) 

clean:
	rm -rf *.o *.c~ Makefile~
	@for bin in $(TARGET); do\
		echo "rm -rf $$bin"; \
		rm -rf $$bin; \
	done
server: $(SERVER_OBJ)
	@echo "making: "$@
	@$(GCC) -o $@ $(CFLAG) $(SERVER_OBJ)
client: $(CLIENT_OBJ)
	@echo "making: "$@
	@$(GCC) -o $@ $(CFLAG) $(CLIENT_OBJ)

