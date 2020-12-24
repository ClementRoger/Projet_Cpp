all: etape1 etape2 clean

etape1: main.cc
	g++ -c Jeu.cc
	g++ -c main.cc

etape2: main.o Jeu.o
	g++ -o exe main.o Jeu.o -lsfml-graphics -lsfml-window -lsfml-system 

clean:
	rm -rf *.o
