gcc:
	g++ -O3 -march=native -cstd=c++11 main.cpp

clang:
	clang++ -O3 -march=native -cstd=c++11 main.cpp

msvc110:
	cl /Ox main.cpp
