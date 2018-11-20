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
	rm $(EXE)1.out $(EXE)2.out $(EXE)3.out

runprod:
	./$(EXE)1.out & ./$(EXE)2.out & ./$(EXE)3.out

buildcons:
	$(CC) -std=$(VER) -pthread -o HW9.out hw9-dingeldein.cpp

cleancons:
	rm HW9.out

runcons:
	./HW9.out

cleanoutput:
	rm *.txt