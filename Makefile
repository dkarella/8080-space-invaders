CC=clang
CFLAGS=-std=c99 -Wall -Werror

all: main

cpu.o: cpu.c
	$(CC) $(CFLAGS) -c cpu.c -o cpu.o

disassembler.o: disassembler.c
	$(CC) $(CFLAGS) -c disassembler.c -o disassembler.o

main: main.c cpu.o disassembler.o
	$(CC) $(CFLAGS) -o main main.c cpu.o disassembler.o

clean:
	rm main cpu.o disassembler.o

run: main
	./main rom/invaders