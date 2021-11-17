CC = g++
INCLUDE_DIR := include
SRC := src
# LIBS=-lsfml-graphics -lsfml-window -lsfml-system 


all: objdir obj/simAnnealing.o obj/Agent.o obj/Genetic.o obj/main.o
	$(CC) -o simAnnealing-app obj/simAnnealing.o obj/Agent.o obj/Genetic.o obj/main.o 
	rm -r obj
	
objdir:
	mkdir -p obj

obj/simAnnealing.o: $(SRC)/simAnnealing.cc
	$(CC) -o obj/simAnnealing.o -I$(INCLUDE_DIR) -c $(SRC)/simAnnealing.cc

obj/Agent.o: $(SRC)/Agent.cc
	$(CC) -o obj/Agent.o -I$(INCLUDE_DIR) -c $(SRC)/Agent.cc

obj/Genetic.o: $(SRC)/Genetic.cc
	$(CC) -o obj/Genetic.o -I$(INCLUDE_DIR) -c $(SRC)/Genetic.cc

obj/main.o: $(SRC)/main.cc
	$(CC) -o obj/main.o -I$(INCLUDE_DIR) -c $(SRC)/main.cc

clean:
	rm -r obj