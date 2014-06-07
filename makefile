gcc:
	g++ -O3 -march=native -std=c++11 main.cpp -o fibint

clang:
	clang++ -O3 -std=c++11 main.cpp -o fibint

msvc:
	cl /W4 /Ox /GL main.cpp /Fefibint
