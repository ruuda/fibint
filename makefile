gcc:
	g++ -O3 -march=native -std=c++11 main.cpp

clang:
	clang++ -O3 -std=c++11 main.cpp

msvc:
	cl /W4 /Ox main.cpp
