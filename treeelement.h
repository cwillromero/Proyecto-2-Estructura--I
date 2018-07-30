#pragma once
#include <string>
#include <iostream>
using namespace std;

class TreeElement{
public:
	string _element;
	int _frecuency;
	TreeElement();
	TreeElement(string);
	TreeElement(string,int);
	~TreeElement();
};