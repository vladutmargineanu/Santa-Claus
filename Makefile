CC=gcc
CFLAGS=-Wall
SRC=tema3.c
EXE=christmas

build: $(EXE)

$(EXE): tema3.o
	        $(CC) tema3.o -o $(EXE)
		        
tema3.o: $(SRC)
	        $(CC) $(CFLAGS) -c $(SRC) -o tema3.o

clean: 
	        rm -f tema3.o $(EXE)                                                                               
		                               
