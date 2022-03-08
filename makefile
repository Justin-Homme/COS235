
CC=cc -g

Driver:   Driver.c Process.o ProcessTable.o
	$(CC) -o Driver Driver.c Process.o ProcessTable.o

Process.o:  Process.c Process.h
	$(CC) -c Process.c

ProcessTable.o:  ProcessTable.c ProcessTable.h
	$(CC) -c ProcessTable.c

clean:
	rm -f Driver *.o
