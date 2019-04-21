prog=trab1
extras = readShader.cpp matrixArith.cpp
# Caminho para glad
glad=src/glad.c
all:
	g++ -Wall -lm -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o $(prog) $(prog).cpp $(extras) $(glad)
run:
	./$(prog)
