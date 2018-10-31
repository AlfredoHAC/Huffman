debug: main.o huffman.o huffTree.o converter.o
	g++ bin/main.o bin/huffman.o bin/huffTree.o bin/converter.o -o bin/huff -g -Wall -std=c++17 

huff: main.o huffman.o huffTree.o converter.o
	g++ bin/main.o bin/huffman.o bin/huffTree.o bin/converter.o -o bin/huff -Wall -std=c++17

huffman.o: src/huffman.cpp
	g++ src/huffman.cpp -o bin/huffman.o -c -I include/ -Wall -std=c++17

huffTree.o: src/huffTree.cpp
	g++ src/huffTree.cpp -o bin/huffTree.o -c -I include/ -Wall -std=c++17

main.o: src/main.cpp
	g++ src/main.cpp -o bin/main.o -c -I include/ -Wall -std=c++17

converter.o: src/converter.cpp
	g++ src/converter.cpp -o bin/converter.o -c -I include/ -Wall -std=c++17