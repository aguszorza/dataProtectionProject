cmake_minimum_required(VERSION 3.15)
project(Pailler)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-lgmpxx -lgmp)

add_executable(Pailler main.cpp Mpz.cpp Mpz.h Generator.cpp Generator.h Paillier.cpp Paillier.h DataHider.cpp DataHider.h Histogram.cpp Histogram.h Utils.cpp Utils.h Difference.cpp Difference.h TattooAggregator.cpp TattooAggregator.h Matrix.cpp Matrix.h Parser.cpp Parser.h Encoder.cpp Encoder.h)