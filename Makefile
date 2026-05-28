all: compile link
compile:
	g++ -std=c++17 -I/usr/local/include -c main.cpp
link:
	g++ main.o -o program -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
clean:
	rm -f program *.o