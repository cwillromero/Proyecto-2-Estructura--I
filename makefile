huffman: main.o treenode.o treeelement.o
	g++ treenode.o main.o treeelement.o -o huffman

main.o:	main.cpp treenode.h treeelement.h
	g++ -c main.cpp

treenode.o: treenode.h treeelement.h treenode.cpp 
	g++ -c treenode.cpp

treeelement.o: treeelement.h treeelement.cpp
	g++ -c treeelement.cpp
