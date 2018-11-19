CC=g++
VER=c++11
SRC=producer
EXE=PRODUCER
LINKS= -pthread

buildprod:
	$(CC) -std=$(VER) $(LINKS) -o $(EXE)1.out $(SRC)1.cpp
	$(CC) -std=$(VER) $(LINKS) -o $(EXE)2.out $(SRC)2.cpp
	$(CC) -std=$(VER) $(LINKS) -o $(EXE)3.out $(SRC)3.cpp

cleanprod:
	rm $(EXE)1 output1.txt
	rm $(EXE)2 output2.txt
	rm $(EXE)3 output3.txt

runprod:
	$(EXE)1 & $(EXE)2 & $(EXE)3