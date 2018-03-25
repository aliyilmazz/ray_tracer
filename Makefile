SRC = main.cpp \
	  Image.cpp \
	  Scene.cpp \
	  Camera.cpp

OBJ = $(SRC:.cpp=.o)
CFLAGS = -std=c++11 -O3

.cpp.o:
	g++ -c $< $(CFLAGS)

all: test

test: $(OBJ)
	g++ $(OBJ) -o raytracer $(CFLAGS)

clean:
	rm -f *.o raytracer *.ppm
