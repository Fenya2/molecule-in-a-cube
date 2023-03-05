OUT=run
VECTOR3LIB=./vector3

all: $(OUT)

$(OUT): main.o $(VECTOR3LIB)/vector3.o
	g++ -o $(OUT) main.o $(VECTOR3LIB)/vector3.o

main.o: main.cpp
	g++ -c -o main.o main.cpp

$(VECTOR3LIB)/vector3.o: $(VECTOR3LIB)/vector3.cpp
	g++ -c -o $(VECTOR3LIB)/vector3.o $(VECTOR3LIB)/vector3.cpp

clean:
	rm -rf *.o $(OUT)
	rm $(VECTOR3LIB)/*.o
