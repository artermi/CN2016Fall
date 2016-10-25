TARGET = pj_server pj_client
GCC = gcc
CFLAGS = -std=c99 -g 

SERVER_OBJ=server.o common.o
CLIENT_OBJ=client.o common.o
LIB=-lm -lbsm
.PHONY:clean

all: $(TARGET)


%.o: %.c
	@echo "making: " $@
	@$(GCC) $< -lpthread -c $(CFLAG) 

clean:
	rm -rf *.o *.c~ Makefile~ *.h~
	@for bin in $(TARGET); do\
		echo "rm -rf $$bin"; \
		rm -rf $$bin; \
	done
pj_server: $(SERVER_OBJ)
	@echo "making: "$@
	@$(GCC) -lpthread -o $@ $(CFLAG) $(SERVER_OBJ)
pj_client: $(CLIENT_OBJ)
	@echo "making: "$@
	@$(GCC) -lpthread -o $@ $(CFLAG) $(CLIENT_OBJ)

