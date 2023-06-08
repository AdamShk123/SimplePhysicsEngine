all: clean compile link

clean:
	rm obj/* main

compile:
	g++ -g src/*.c* -c
	mv *.o obj/

link:
	g++ obj/* -o main -lglfw3 -lgdi32 -lopengl32 #-llua
