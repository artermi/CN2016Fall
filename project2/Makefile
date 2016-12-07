TARGET = project2
GPP = g++
CPPFLAGS = -O2 -std=c++11 -Wall


PJ2_OBJ=
READFILE_OBJ=read_input_file.o test_read_input_file.cpp
LIB=-lm -lbsm
.PHONY:clean

all: $(TARGET)


%.o: %.cpp
	@echo "making: " $@
	@$(GPP) $(CFLAG) 

clean:
	rm -rf *.o *.cpp~ Makefile~ *.h~
	@for bin in $(TARGET); do\
		echo "rm -rf $$bin"; \
		rm -rf $$bin; \
	done
project2: $(PJ2_OBJ)
	@echo "making: "$@
	@$(GPP) $(CFLAG) $(PJ2_OBJ)
trying:$(READFILE_OBJ)
	@echo "making: "$@
	@$(GPP) $(CFLAG) $(trying)

