CC = g++ # compiler
CCFLAGS = -std=c++11 -Wall # compiler flags
LE = g++ # link editor
LEFLAGS =-lm -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lfreeimage -lassimp # link editor flags




LOCAL_LIB = lib
LOCAL_INCLUDE = include
LOCAL_SRC = src

PROG = trab2

SHADERS_PATH = shaders/

OBJECTS = $(LOCAL_LIB)/glad.o $(LOCAL_LIB)/readShader.o $(LOCAL_LIB)/matrixArith.o $(PROG).o \
	$(LOCAL_LIB)/Mesh.o $(LOCAL_LIB)/Model.o # object files

all : $(OBJECTS)
	$(LE) $^ -o $(PROG) -I $(LOCAL_INCLUDE) -L $(LOCAL_LIB)  $(LEFLAGS)  


$(LOCAL_LIB)/%.o : $(LOCAL_SRC)/%.cpp $(LOCAL_INCLUDE)/%.h
	$(CC) $(CCFLAGS) -c -o $@ $< -I$(LOCAL_INCLUDE)
	
$(LOCAL_LIB)/glad.o : $(LOCAL_SRC)/glad.c $(LOCAL_INCLUDE)/glad/glad.h
	$(CC) $(CCFLAGS) -c -o $@ $< -I$(LOCAL_INCLUDE)
	

$(PROG).o : $(PROG).cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I $(LOCAL_INCLUDE)
	

run :
	./$(PROG)


clean : 
	rm $(LOCAL_LIB)/*.o
	rm $(PROG).o
	rm $(PROG)


