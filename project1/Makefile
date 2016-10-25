TARGET = server client
GCC = gcc
CFLAGS = -std=c99 -g 

SERVER_OBJ=server.o common.o
CLIENT_OBJ=client.o common.o
LIB=-lm -lbsm
.PHONY:clean

all: $(TARGET)


%.o: %.c
	@echo "making: " $@
	@$(GCC) $< -pthread -c $(CFLAG) 

clean:
	rm -rf *.o *.c~ Makefile~ *.h~
	@for bin in $(TARGET); do\
		echo "rm -rf $$bin"; \
		rm -rf $$bin; \
	done
server: $(SERVER_OBJ)
	@echo "making: "$@
	@$(GCC) -pthread -o $@ $(CFLAG) $(SERVER_OBJ)
client: $(CLIENT_OBJ)
	@echo "making: "$@
	@$(GCC) -pthread -o $@ $(CFLAG) $(CLIENT_OBJ)

