CC = g++
CFLAGS = -Wall
LFLAGS = -lgmpxx -lgmp
FILE_OUT = Programme

all: main.o Mpz.o Generator.o Paillier.o DataHider.o Histogram.o Difference.o TattooAggregator.o Utils.o Matrix.o Parser.o Encoder.o
	$(CC) $(CFLAGS) -o $(FILE_OUT) main.o Mpz.o Generator.o Paillier.o DataHider.o Histogram.o Difference.o TattooAggregator.o Matrix.o Utils.o Parser.o Encoder.o $(LFLAGS)

main.o: main.cpp Mpz.h
	$(CC) $(CFLAGS) -c -o main.o main.cpp $(LFLAGS)

Mpz.o: Mpz.cpp Mpz.h 
	$(CC) $(CFLAGS) -c -o Mpz.o Mpz.cpp $(LFLAGS)

Generator.o: Generator.cpp Generator.h Mpz.h
	$(CC) $(CFLAGS) -c -o Generator.o Generator.cpp $(LFLAGS)

Paillier.o: Paillier.cpp Paillier.h Mpz.h
	$(CC) $(CFLAGS) -c -o Paillier.o Paillier.cpp $(LFLAGS)

DataHider.o: DataHider.cpp DataHider.h Mpz.h Difference.h
	$(CC) $(CFLAGS) -c -o DataHider.o DataHider.cpp $(LFLAGS)

Histogram.o: Histogram.cpp Histogram.h
	$(CC) $(CFLAGS) -c -o Histogram.o Histogram.cpp $(LFLAGS)

Difference.o: Difference.cpp Difference.h
	$(CC) $(CFLAGS) -c -o Difference.o Difference.cpp $(LFLAGS)

TattooAggregator.o: TattooAggregator.cpp TattooAggregator.h Difference.h Mpz.h
	$(CC) $(CFLAGS) -c -o TattooAggregator.o TattooAggregator.cpp $(LFLAGS)

Matrix.o: Matrix.cpp Matrix.h Mpz.h
	$(CC) $(CFLAGS) -c -o Matrix.o Matrix.cpp $(LFLAGS)

Utils.o: Utils.cpp Utils.h Mpz.h Generator.h Paillier.h DataHider.h Histogram.h Difference.h TattooAggregator.h Matrix.h
	$(CC) $(CFLAGS) -c -o Utils.o Utils.cpp $(LFLAGS)

Parser.o: Parser.cpp Parser.h
	$(CC) $(CFLAGS) -c -o Parser.o Parser.cpp $(LFLAGS)

Encoder.o: Encoder.cpp Encoder.h Mpz.h Matrix.h TattooAggregator.h Paillier.h DataHider.h Generator.h Histogram.h Utils.h
	$(CC) $(CFLAGS) -c -o Encoder.o Encoder.cpp $(LFLAGS)
