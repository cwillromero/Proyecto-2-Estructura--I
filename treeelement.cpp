/******************************************************************************************
Título: Proyecto #2 Codificación usando Árbol de Huffman
Propósito: Leer de un archivo de texto, construir un árbol de Huffman y generar la 
codificación de caracteres del archivo.
Clase: CCC209 – Q3 – 2018
Author: Carlos Wilfredo Romero Maradiaga    11711209
*******************************************************************************************/

#include "treeelement.h"

/*
-Constructor de la clase
-Params: Ninguno
-Returna:No Retorna
-Errores: Ninguno
*/
TreeElement::TreeElement(): _frecuency(1),_element(NULL){
}

/*
-Constructor de la clase
-Params: int _frecuency; representa la frecuencia del TreeElement
-Returna:No Retorna
-Errores: Ninguno
*/
TreeElement::TreeElement(string element): _frecuency(1){
    _element=element;
}

/*
-Constructor de la clase
-Params: string _element; representa el indentificador que tendrá el TreeElement, 
int _frecuency; representa la frecuencia del TreeElement
-Returna:No Retorna
-Errores: Ninguno
*/
TreeElement::TreeElement(string element, int frecuency): _element(element), _frecuency(frecuency){
}


/*
-Destrcutor de la clase
-Params: Ninguno
-Returna:No Retorna
-Errores: Ninguno
*/
TreeElement::~TreeElement(){
}