CCompiler = gcc
CurrentDirectory = -I.

20050111074: 20050111074.c
	$(CCompiler) -o $@ $^ $(CurrentDirectory)

clear:
	rm 20050111074
	rm output.txt

run:
	./20050111074 5 6 output.txt
