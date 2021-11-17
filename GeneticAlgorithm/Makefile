CC = g++
INCLUDE_DIR := include
SRC := src
LIBS=-lsfml-graphics -lsfml-window -lsfml-system 


all: objdir obj/Agent.o  obj/main.o obj/Genetic.o obj/draw.o
	$(CC) -o gen-app obj/Agent.o obj/main.o obj/Genetic.o obj/draw.o $(LIBS)
	rm -r obj
objdir:
	mkdir -p obj
obj/Agent.o: $(SRC)/Agent.cc
	$(CC) -o obj/Agent.o -I$(INCLUDE_DIR) -c $(SRC)/Agent.cc
obj/Genetic.o: $(SRC)/Genetic.cc
	$(CC) -o obj/Genetic.o -I$(INCLUDE_DIR) -c $(SRC)/Genetic.cc 
obj/main.o: $(SRC)/main.cc
	$(CC) -o obj/main.o -I$(INCLUDE_DIR) -c $(SRC)/main.cc $(LIBS)
obj/draw.o: $(SRC)/draw.cc
	$(CC) -o obj/draw.o -I$(INCLUDE_DIR) -c $(SRC)/draw.cc $(LIBS)
clean:
	rm -r obj
