huff: main.o huffman.o huffTree.o
	g++ bin/main.o bin/huffman.o bin/huffTree.o -o bin/huff -Wall -std=c++17

huffman.o: src/huffman.cpp
	g++ src/huffman.cpp -o bin/huffman.o -c -I include/ -Wall -std=c++17

huffTree.o: src/huffTree.cpp
	g++ src/huffTree.cpp -o bin/huffTree.o -c -I include/ -Wall -std=c++17

main.o: src/main.cpp
	g++ src/main.cpp -o bin/main.o -c -I include/ -Wall -std=c++17