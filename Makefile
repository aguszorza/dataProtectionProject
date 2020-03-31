CC = g++
CFLAGS = -Wall
LFLAGS = -lgmpxx -lgmp
FILE_OUT = Programme

all: main.o Mpz.o Generator.o Paillier.o DataHider.o Histogram.o
	$(CC) $(CFLAGS) -o $(FILE_OUT) main.o Mpz.o Generator.o Paillier.o DataHider.o Histogram.o $(LFLAGS)

main.o: main.cpp Mpz.h
	$(CC) $(CFLAGS) -c -o main.o main.cpp $(LFLAGS)

Mpz.o: Mpz.cpp Mpz.h 
	$(CC) $(CFLAGS) -c -o Mpz.o Mpz.cpp $(LFLAGS)

Generator.o: Generator.cpp Generator.h Mpz.h
	$(CC) $(CFLAGS) -c -o Generator.o Generator.cpp $(LFLAGS)

Paillier.o: Paillier.cpp Paillier.h Mpz.h
	$(CC) $(CFLAGS) -c -o Paillier.o Paillier.cpp $(LFLAGS)

DataHider.o: DataHider.cpp DataHider.h Mpz.h
	$(CC) $(CFLAGS) -c -o DataHider.o DataHider.cpp $(LFLAGS)

Histogram.o: Histogram.cpp Histogram.h
	$(CC) $(CFLAGS) -c -o Histogram.o Histogram.cpp $(LFLAGS)

