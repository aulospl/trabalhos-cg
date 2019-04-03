prog=test
all:
	g++ -Wall -lm -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o $(prog) $(prog).cpp src/glad.c
run:
	echo $(prog)
