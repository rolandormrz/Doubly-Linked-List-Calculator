CC=g++
CFLAGS=
INC=
LIB=

all:  calculator

calculator:  main.o CalcList.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

.cpp.o:
	$(CC) $(CFLAGS) $(INC) -c -o $@ $^ 

main.cpp:  CalcList.hpp

CalcList.cpp:  CalcListInterface.hpp

clean:
	rm -f *.o calculator