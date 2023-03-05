TARGET = program

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o
main.o: main.cpp
	g++ -c -o main.o main.cpp
$(TARGET): main.o ./vector3/vector3.o
	g++ -o $(TARGET) main.o ./vector3/vector3.o
