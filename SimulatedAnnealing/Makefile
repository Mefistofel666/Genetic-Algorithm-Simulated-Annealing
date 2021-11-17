CC = g++
INCLUDE_DIR := include
SRC := src
LIBS=-lsfml-graphics -lsfml-window -lsfml-system 


all: objdir obj/simAnnealing.o  obj/main.o obj/draw.o
	$(CC) -o simAnnealing-app obj/simAnnealing.o obj/main.o obj/draw.o $(LIBS)
	rm -r obj
objdir:
	mkdir -p obj
obj/simAnnealing.o: $(SRC)/simAnnealing.cc
	$(CC) -o obj/simAnnealing.o -I$(INCLUDE_DIR) -c $(SRC)/simAnnealing.cc
obj/draw.o: $(SRC)/draw.cc
	$(CC) -o obj/draw.o -I$(INCLUDE_DIR) -c $(SRC)/draw.cc $(LIBS)
obj/main.o: $(SRC)/main.cc
	$(CC) -o obj/main.o -I$(INCLUDE_DIR) -c $(SRC)/main.cc $(LIBS)
clean:
	rm -r obj
