cmake_minimum_required(VERSION 3.15)
project(Pailler)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-lgmpxx -lgmp)

add_executable(Pailler main.cpp Mpz.cpp Mpz.h Generator.cpp Generator.h Paillier.cpp Paillier.h DataHider.cpp DataHider.h)