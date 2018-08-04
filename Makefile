CXX = g++
CXXFLAGS = -O3

.c.o: $(CXX) -c $< -o $@

all: gen-string.exe string-prime.exe

gen-string.exe: gen-string.cpp readbdf.cpp
	$(CXX) $(CXXFLAGS) $< -o gen-string

string-prime.exe: string-prime.cpp miller-rabin-gmp.o
	$(CXX) $(CXXFLAGS) string-prime.cpp miller-rabin-gmp.o -o string-prime -lgmp -lgmpxx
