prog=test
extras=
all:
	g++ -Wall -lm -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o $(prog) $(prog).cpp $(extras) src/glad.c
run:
	./$(prog)
