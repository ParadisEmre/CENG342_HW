CCompiler = mpicc
CurrentDirectory = -I.

20050111074: 20050111074.c
	$(CCompiler) -g -Wall -o $@ $^ $(CurrentDirectory)

clear:
	rm 20050111074
	rm output.txt

runLargeW1:
	mpirun -n 1 ./20050111074 1074 1074 output.txt

runLargeW2:
	mpirun -n 2 ./20050111074 1074 1074 output.txt

runLargeW3:
	mpirun -n 3 ./20050111074 1074 1074 output.txt

runLargeW4:
	mpirun -n 4 ./20050111074 1074 1074 output.txt

runSmallW1:
	mpirun -n 1 ./20050111074 174 174 output.txt

runSmallW2:
	mpirun -n 2 ./20050111074 174 174 output.txt

runSmallW3:
	mpirun -n 3 ./20050111074 174 174 output.txt

runSmallW4:
	mpirun -n 4 ./20050111074 174 174 output.txt