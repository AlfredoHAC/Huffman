huff: main.o huffman.o huffTree.o converter.o
	g++ src/main.o src/huffman.o src/huffTree.o src/converter.o -o huff -Ofast -Wall -std=c++17

debug:
	g++ src/main.cpp src/huffman.cpp src/huffTree.cpp src/converter.cpp -I include -o huff -g3 -Wall -std=c++17

huffman.o: src/huffman.cpp
	g++ src/huffman.cpp -o src/huffman.o -c -I include/ -Wall -std=c++17

huffTree.o: src/huffTree.cpp
	g++ src/huffTree.cpp -o src/huffTree.o -c -I include/ -Wall -std=c++17

main.o: src/main.cpp
	g++ src/main.cpp -o src/main.o -c -I include/ -Wall -std=c++17

converter.o: src/converter.cpp
	g++ src/converter.cpp -o src/converter.o -c -I include/ -Wall -std=c++17

.PHONY: clean

clean:
	-rm src/*.o $(objects) huff

