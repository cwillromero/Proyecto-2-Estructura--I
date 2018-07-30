huffman: treenode.o main.o treeelement.o
	g++ treenode.o main.o treeelement.h -o huffman

main.o:	main.cpp
	g++ -c main.cpp

treenode.o: treenode.h treenode.cpp treeelement.h
	g++ -c treenode.cpp

treeelement.o: treeelement.h treeelement.cpp
	g++ -c treeelement.cpp
