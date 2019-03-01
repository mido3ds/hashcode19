all: out
	g++ a.cpp -O3 && ./a.exe

out:
	mkdir out

run: out
	./a.exe