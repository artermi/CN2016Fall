TARGET = project2
TEST = trying
GPP = g++
CPPFLAGS = -O2 -std=c++11 -Wall


PJ2_OBJ=read_input_file.o pj2_main.o
READFILE_OBJ=read_input_file.o test_read_input_file.o
LIB=-lm -lbsm
.PHONY:clean

all: $(TARGET)


%.o: %.cpp
	@echo "making: " $@
	@$(GPP) $< -c $(CPPFLAG) 

clean:
	rm -rf *.o *.cpp~ Makefile~ *.h~
	@for bin in $(TARGET) $(TEST); do\
		echo "rm -rf $$bin"; \
		rm -rf $$bin; \
	done
project2: $(PJ2_OBJ)
	@echo "making: "$@
	@$(GPP) -o $@ $(CFLAG) $(PJ2_OBJ)

trying: $(READFILE_OBJ)
	@echo "making: "$@
	@$(GPP) -o $@ $(CFLAG) $(READFILE_OBJ)

