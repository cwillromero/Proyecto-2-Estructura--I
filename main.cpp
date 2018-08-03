/******************************************************************************************
Título: Proyecto #2 Codificación usando Árbol de Huffman
Propósito: Leer de un archivo de texto, construir un árbol de Huffman y generar la 
codificación de caracteres del archivo.
Clase: CCC209 – Q3 – 2018
Author: Carlos Wilfredo Romero Maradiaga    11711209
*******************************************************************************************/

#include "treenode.h"
#include "treeelement.h"
#include <string.h>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

vector<string> GetText(char*[]);
vector <TreeElement*> GetFrecuencyVector(vector <string>);
bool SortTreeElements(TreeElement*, TreeElement*);
bool SortTreeNodes(TreeNode*, TreeNode*);
vector <TreeNode*>GetTree(vector <TreeElement*>);
string Huffman(TreeNode*,TreeElement*);

int main(int argc, char* argv[]){
    //Vector del Texto
    vector<string> text;
    if(argc<2){
        cout<<"Parámetros Insuficientes."<<endl;
        return 0;
    }
    //Llena el vector del Texto
    text=GetText(argv);
    if(text.size()==0){
        cout<<"No se pudo abrir el archivo."<<endl;
        return 0;
    }
    //Vector de TreeElements
    vector <TreeElement*> characters;
    //Vector de TreeNodes
    vector <TreeNode*> tree;
    //LLena el vector de TreeElements
    characters=GetFrecuencyVector(text);
    //Ordena el vector de TreeElements
    sort(characters.begin(), characters.end(), SortTreeElements);
    //Obtiene el arbol completo de TreeElements
    tree=GetTree(characters);
    //Codificación Huffman por cada caracter
    for(int i=0; i<characters.size(); i++){
        string code;
        code=Huffman(tree[0], characters[i]);
        if(int(characters[i]->_element[0])==32){
            cout<<"{key: "<<"SP"<<", code: "<<code<<"}"<<endl;
        }else if(int(characters[i]->_element[0])==10){
            cout<<"{key: "<<"LF"<<", code: "<<code<<"}"<<endl;
        }else if(int(characters[i]->_element[0])==13){
            cout<<"{key: "<<"CR"<<", code: "<<code<<"}"<<endl;
        }else{
            cout<<"{key: "<<characters[i]->_element<<", code: "<<code<<"}"<<endl;
        }
    }
    for(int i=0; i<characters.size(); i++){
        if(characters[i]!=nullptr){ 
            delete characters[i];
        }
    }
    characters.clear();
    delete tree[0];
    tree.clear();
}

/*
-Obtiene el texto del archivo enviado como parametro
-Params: char* argv[]; representa la cadena que tiene el nombre del archivo de texto
-Returna:un vector de string en donde va el texto del archivo
-Errores: Si no se abre el archivo retorna un vector vacio (size 0), en el main está la condicion 
para detener la ejecución si esto pasa
*/
vector<string> GetText(char* argv[]){
    vector <string> retVal;
    char character;
    fstream file;
    file.open (argv[1] , ios::in);
    if (file.is_open()) {
        while (file.get(character)) {
            if(int(character)>0){
                retVal.push_back(string(1,character));
            }
        }
        file.close();
    }
    return retVal;
}

/*
-Crea el vector de Frecuencias de cada caracter del texto
-Params: vector<string> text; representa el vector de texto a partir del cual
se genera el vector de TreeElements
-Returna:el vector de TreeElements con las frecuencias ya calculadas
-Errores: Ninguno
*/
vector<TreeElement*> GetFrecuencyVector(vector<string> text){
    vector <TreeElement*> characters;
    TreeElement* element=new TreeElement(text[0]);
    characters.push_back(element);
    string character;
    for(int i=1; i<text.size(); i++){
        int cont=0;
        character=text[i];
        for(int j=0; j<characters.size(); j++){
            if(characters[j]->_element==character){
                characters[j]->_frecuency++;
                cont++;
            }
        }
        if(cont==0){
            element=new TreeElement(character);
            characters.push_back(element);
        }
    }
    return characters;
}

/*
-Ordena el vector de TreeElements por frecuencia descendentemente
-Params: TreeElement* treeElementA; representa el inicio del vector de treeElements, 
TreeElement *treeElementB representa el final del vector de treeElements,
-Returna:el vector de TreeElements ordenado
-Errores: Si las frecuencias son iguales, ordena alfabeticamente los elementos con frecuencias iguales
*/
bool SortTreeElements(TreeElement* treeElementA, TreeElement *treeElementB) { 
    if(treeElementA->_frecuency == treeElementB->_frecuency){
        return treeElementA->_element > treeElementB->_element ;
    }else{
        return treeElementA->_frecuency > treeElementB->_frecuency;
    }
}

/*
-Ordena el vector de TreeNodes por frecuencia descendentemente
-Params: TreeNode* TreeNodeA; representa el inicio del vector de TreeNodes, 
TreeNode* TreeNodeB representa el final del vector de TreeNodes,
-Returna:el vector de TreeNodes ordenado
-Errores: Si las frecuencias son iguales, ordena alfabeticamente los elementos con frecuencias iguales
*/
bool SortTreeNodes(TreeNode* treeNodeA, TreeNode *treeNodeB) { 
    if(treeNodeA->GetData()._frecuency == treeNodeB->GetData()._frecuency){
        return treeNodeA->GetData()._element > treeNodeB->GetData()._element;
    }else{
        return treeNodeA->GetData()._frecuency > treeNodeB->GetData()._frecuency;
    }
}

/*
-Crea el arbol de TreeElements
-Params: vector <TreeElement*> characters; representa el vector a partir del cual se crea el arbol
-Returna:el vector de TreeNodes solo con un elemento, el arbol de Huffman
-Errores: Mientras el vector de TreeNodes tenga un tamaño mayor a uno, 
seguira tomando y creando nuevos TreeNodes
*/
vector <TreeNode*>GetTree(vector <TreeElement*> characters){
    //Vector de TreeNodes
    vector<TreeNode*> treeVector;
    TreeNode* treeNode;
    //LLena le vector con TreeNodes de cada element del vector de treeElement
    for(int i=0; i<characters.size(); i++){
        treeNode=(new TreeNode(*characters[i]));
        treeVector.push_back(treeNode);
    }
    //Ordena el vector de TreeNodes
    sort(treeVector.begin(), treeVector.end(), SortTreeNodes);
    while (treeVector.size()>1){
        stringstream nameTree;
        int frecuency;
        //Concatena el nombre de los ultimos dos TreeNodes del vector de TreeNodes
        nameTree<<treeVector[treeVector.size()-1]->GetData()._element<<treeVector[treeVector.size()-2]->GetData()._element;
        //Suma la frecuencia de los ultimos dos TreeNodes del vector de TreeNodes
        frecuency=treeVector[treeVector.size()-1]->GetData()._frecuency+treeVector[treeVector.size()-2]->GetData()._frecuency;
        //Crea un nuevo TreeNode con hijos, los dos ultimos TreeNodes del vector
        TreeElement* combinatedNode=new TreeElement(nameTree.str(),frecuency);
        treeNode=new TreeNode(*combinatedNode);
        treeNode->AddChild(treeVector[treeVector.size()-2]);
        treeNode->AddChild(treeVector[treeVector.size()-1]);
        //Elimina ultimos dos TreeNodes y agrega el nuevo TreeNode el vector de TreeNodes
        treeVector.pop_back();
        treeVector.pop_back();
        treeVector.push_back(treeNode);
        //Ordena el vector de TreeNodes
        sort(treeVector.begin(), treeVector.end(), SortTreeNodes);
    }
    return treeVector;
}

/*
-Crea el codigo Huffman del TreeElement
-Params: TreeNode* treeNode; representa el arbol de Huffman
TreeElement* treeElement; representa el TreeElement del cual se hará la codificación
-Returna:un string con la codificación
-Errores: Mientras no sea hoja el nodo, seguira adentrándose al arbol
*/
string Huffman(TreeNode* treeNode, TreeElement* treeElement){
    TreeNode* tree=treeNode;
    vector< TreeNode*> stack;
    stringstream code;
   while(!tree->IsLeaf()){
        if(tree->GetChildren()[0]->GetData()._element.find(treeElement->_element) != std::string::npos){
            tree=tree->GetChildren()[0];
                          code<<"1";
            if(tree->GetData()._element==treeElement->_element){
                return code.str();
            }
        }else{
            tree=tree->GetChildren()[1];
            code<<"0";
            if(tree->GetData()._element==treeElement->_element){
                return code.str();
            }
            
        }
    }
}