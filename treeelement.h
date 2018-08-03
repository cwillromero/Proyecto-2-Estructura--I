/******************************************************************************************
Título: Proyecto #2 Codificación usando Árbol de Huffman
Propósito: Leer de un archivo de texto, construir un árbol de Huffman y generar la 
codificación de caracteres del archivo.
Clase: CCC209 – Q3 – 2018
Author: Carlos Wilfredo Romero Maradiaga    11711209
*******************************************************************************************/

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
