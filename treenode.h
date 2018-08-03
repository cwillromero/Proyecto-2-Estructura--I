/******************************************************************************************
Título: Proyecto #2 Codificación usando Árbol de Huffman
Propósito: Leer de un archivo de texto, construir un árbol de Huffman y generar la 
codificación de caracteres del archivo.
Clase: CCC209 – Q3 – 2018
Author: Carlos Wilfredo Romero Maradiaga    11711209
*******************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "treeelement.h"

using std::string;
using namespace std;

class TreeNode{
	vector<TreeNode*> _children;
	TreeNode* _parent;
	TreeElement* _data;
public:
	TreeNode(const TreeElement&);
	TreeNode(const TreeElement&,TreeNode*);
	~TreeNode();
	vector<TreeNode*>& GetChildren(); 
	void SetParent(TreeNode*);
	void AddChild(const TreeElement&);
	void AddChild(TreeNode*);
	TreeElement GetData()const; 
	void SetData(const TreeElement&);
	bool IsRoot()const;
	bool IsLeaf()const;
};

