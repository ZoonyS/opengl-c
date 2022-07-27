all: compile run

compile:
	mkdir -p bin
	gcc -o bin/opengl-c -Iinclude `find src -name "*.c"` -lglfw3 -ldl -lm -lGL -lGLU -lX11

run:
	./bin/opengl-c

clean:
	rm -rf bin
