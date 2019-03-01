EXE=solution.exe

all: out compile run

out:
	mkdir out

compile: a.cpp 
	g++ a.cpp -O3 -o $(EXE)

run: out compile 
	./$(EXE)

clean:
	rm $(EXE)