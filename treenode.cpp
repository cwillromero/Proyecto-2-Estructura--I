/******************************************************************************************
Título: Proyecto #2 Codificación usando Árbol de Huffman
Propósito: Leer de un archivo de texto, construir un árbol de Huffman y generar la 
codificación de caracteres del archivo.
Clase: CCC209 – Q3 – 2018
Author: Carlos Wilfredo Romero Maradiaga    11711209
*******************************************************************************************/

#include "treenode.h"

#include <sstream> 
#include <iostream> 
#include <string> 

/*
-Constructor de la clase
-Params: TreeElement& data; representa el data que trendrá el TreeNode
-Returna:No Retorna
-Errores: Ninguno
*/
TreeNode::TreeNode(const TreeElement& data) {
    _data = new TreeElement(data._element, data._frecuency); 
    _parent = nullptr; 
}

/*
-Constructor de la clase
-Params: TreeElement& data; representa el data que trendrá el TreeNode, 
TreeNode* parent; representa el padre del TreeNode
-Returna:No Retorna
-Errores: Ninguno
*/
TreeNode::TreeNode(const TreeElement& data, TreeNode* parent) {
    _parent = parent; 
    _data = new TreeElement(data._element, data._frecuency); 
	_parent-> AddChild(this); 
}

/*
-Destructor de la clase
-Params: Ninguno
-Returna:No Retorna
-Errores: Ninguno
*/
TreeNode::~TreeNode() {
    if (this != nullptr) {
    	if ( ! this->IsLeaf()) {
    		for (int i = 0; i < _children.size(); i++) {
    		delete _children[i]; 
    		}
	}
	if (_data != nullptr)
		delete _data; 
	}
}

/*
-Obtiene los hijos del TreeNode
-Params: Ninguno
-Returna: Retorna el vector de hijos del TreeNode
-Errores: Ninguno
*/
vector < TreeNode*>& TreeNode::GetChildren() {
    return _children; 
}

/*
-Cambia de Padre al TeeeNode
-Params: TreeNode* parent, representa el TreeNode que será padre de éste TreeNode
-Returna: No retorna
-Errores: Ninguno
*/
void TreeNode::SetParent(TreeNode* parent) {
     _parent = nullptr; 
    _parent = parent; 
}

/*
-Agrega un nuevo hijo al TreeNode creandolo desde la función
-Params: TreeElement& data, representa TreeElement al partir del cual se crea 
un nuevo TreeNode y el constructor llama a la funcion AddChild  que tiene como parametros un TreeNode
-Returna: No retorna
-Errores: Ninguno
*/
void TreeNode::AddChild(const TreeElement& data) {
    TreeNode * newChild = new TreeNode(data, this); 
}

/*
-Agrega un nuevo hijo al TreeNode agregandolo al vector de hijos y a éste hijo se le setea un padre
-Params: TreeNOde data, representa TreeNode que se agrega al vector de hijos
-Returna: No retorna
-Errores: Ninguno
*/
void TreeNode::AddChild(TreeNode* child) {
	_children.insert(_children.begin(), child); 
	child->SetParent(this); 
}

/*
-Obtiene el TreeElement que tiene como data el TreeNode
-Params: Ninguno
-Returna: retorna el TreeElement que tiene como data el TreeNode
-Errores: Ninguno
*/
TreeElement TreeNode::GetData()const {
	return * _data; 
}

/*
-Cambia el data actual de este TreeNode por uno nuevo
-Params:  TreeElement& data, representa el treeElement que se seteara al _data deL treenode
-Returna: No retorna
-Errores: Ninguno
*/
void TreeNode::SetData(const TreeElement& data) {
	_data = nullptr; 
	_data = new TreeElement(data._element, data._frecuency); 
}

/*
-Determina si el TreeNode es raiz o no
-Params:  Ninguno
-Returna: True si es raiz, false si no.
-Errores: Ninguno
*/
bool TreeNode::IsRoot()const {
	if (_parent == nullptr)
		return true; 
	else
        return false; 
}

/*
-Determina si el TreeNode es hija o no
-Params:  Ninguno
-Returna: True si es hoja, false si no.
-Errores: Ninguno
*/
bool TreeNode::IsLeaf()const {
	if (_children.size() == 0)
		return true; 
	else
        return false; 
}
