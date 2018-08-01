#include <string>
#include <iostream>
using namespace std;
#ifndef TREEELEMENT_H
#define TREEELEMENT_H

class TreeElement{
public:
	string _element;
	int _frecuency;
	TreeElement();
	TreeElement(string);
	TreeElement(string,int);
	~TreeElement();
};
#endif
