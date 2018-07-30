#include "treeelement.h"

TreeElement::TreeElement(): _frecuency(1),_element(NULL){
}

TreeElement::TreeElement(string element): _frecuency(1){
    _element=element;
}

TreeElement::TreeElement(string element, int frecuency): _element(element), _frecuency(frecuency){
}

TreeElement::~TreeElement(){
}