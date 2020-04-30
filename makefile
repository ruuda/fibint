gcc:
	g++ -O3 -march=native -std=c++11 main.cpp -o fibint

clang:
	clang++ -O3 -std=c++11 main.cpp -o fibint

msvc:
	cl /W4 /Ox /GL main.cpp /Fefibint

msvc-pgo:
	cl /W4 /Ox /GL /c main.cpp
	link /ltcg:pgi /pgd:fibint.pgd main.obj /out:fibint.exe
	fibint print u8
	fibint print u16
	fibint print u32
	fibint print u64
	link /ltcg:pgo /pgd:fibint.pgd main.obj /out:fibint.exe

msvc-clean:
	del main.obj fibint!?.pgc fibint.pgd fibint.exe
