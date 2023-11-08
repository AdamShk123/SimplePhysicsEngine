all: clean compile link

FILES := src/main.cpp src/batch_renderer.cpp src/glad.c

LIBS := -l glfw -lGL

clean:
	rm obj/* main.exe

compile:
	g++ --std=c++17 -g ${FILES} -c
	mv *.o obj/

link:
	g++ obj/* -o main.exe ${LIBS}
