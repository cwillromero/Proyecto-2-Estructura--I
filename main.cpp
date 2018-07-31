#include "treenode.h"
#include "treeelement.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

vector<string> GetText(char*[]);
vector <TreeElement*> GetFrecuencyVector(vector <string>);
vector <TreeElement*> SortCharacters(vector <TreeElement*>);
void PrintFrecuencyVector(vector <TreeElement*>);
vector <TreeNode*>GetTree(vector <TreeElement*>);

void PruebaArboles();
void Huffman(vector <TreeElement*>);

int main(int argc, char* argv[]){
    vector<string> text;
    if(argc<2){
        cout<<"Parámetros Insuficientes."<<endl;
        return 0;
    }
    text=GetText(argv);
    if(text.size()<1)
        return 0;

    vector <TreeElement*> characters;
    vector <TreeNode*> tree;
    characters=GetFrecuencyVector(text);
    characters=SortCharacters(characters);
    PrintFrecuencyVector(characters);
    tree=GetTree(characters);
}

vector<string> GetText(char* argv[]){
    vector <string> retVal;
    char character;
    fstream file;
    file.open (argv[1] , ios::in);
    if (file.is_open()) {
        while (file.get(character)) {
            if(int(character)==32){
                retVal.push_back("SP");
            }else if(int(character)==10){
                retVal.push_back("LF");
            }else if(int(character)==13){
                retVal.push_back("CR");
            }else{
                retVal.push_back(string(1,character));
            }
        }
        file.close();
    }
    return retVal;
}

vector<TreeElement*> GetFrecuencyVector(vector<string> text){
    vector <TreeElement*> characters;
    TreeElement* element=new TreeElement(text[0]);
    characters.push_back(element);
    string character;
    cout<<"Size Text"<<text.size()<<endl;
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

vector<TreeElement*> SortCharacters(vector<TreeElement*> characters){
    for(int i=0;i<characters.size();i++){
        for(int j=i+1;j<characters.size();j++){
            if(characters[i]->_frecuency<characters[j]->_frecuency){     
                TreeElement* temp=characters[i]; 
                characters[i]=characters[j]; 
                characters[j]=temp; 
            }
            if(characters[i]->_frecuency==characters[j]->_frecuency){
                if(int(characters[i]->_element[0])>int(characters[j]->_element[0])){
                    TreeElement* temp=characters[i]; 
                    characters[i]=characters[j]; 
                    characters[j]=temp; 
                }
            }
        }
    }
    return characters;
}

void PrintFrecuencyVector(vector <TreeElement*> characters){
    int cont=0;
    for(int j=0; j<characters.size(); j++){
        cont=cont+characters[j]->_frecuency;
        cout<<"Character: "<<characters[j]->_element<<"     Frecuency: "<<characters[j]->_frecuency<<endl;
    }
    cout<<cont<<endl;
}

vector <TreeNode*>GetTree(vector <TreeElement*> characters){
    vector<TreeNode*> treeVector;
    for(int i=0; i<characters.size(); i++){
        treeVector.push_back(new TreeNode(*characters[i]));
    }
    TreeNode* treeNode;
    while (characters.size()>1){
        stringstream nameTree;
        int frecuency;
        TreeElement* leftNode=characters[characters.size()-1];
        characters.pop_back();
        TreeElement* rightNode=characters[characters.size()-1];
        nameTree<<leftNode->_element<<rightNode->_element;
        frecuency=rightNode->_frecuency+leftNode->_frecuency;
        TreeElement* combinatedNode=new TreeElement(nameTree.str(),frecuency);
        characters.pop_back();
        characters.push_back(combinatedNode);
        treeNode=new TreeNode(*combinatedNode);
        treeNode->AddChild(treeVector[treeVector.size()-2]);
        treeNode->AddChild(treeVector[treeVector.size()-1]);
        treeVector.pop_back();
        treeVector.pop_back();
        treeVector.push_back(treeNode);

        for(int i=0;i<characters.size();i++){
            for(int j=i+1;j<characters.size();j++){
                if(characters[i]->_frecuency<characters[j]->_frecuency){
                    TreeNode* tmp=treeVector[i];
                    TreeElement* temp=characters[i]; 
                    characters[i]=characters[j]; 
                    treeVector[i]=treeVector[j];
                    characters[j]=temp; 
                    treeVector[j]=tmp;
                }
            }
        }
        cout<<"Element: "<<treeNode->GetData()._element<<" Frecuency: "<<treeNode->GetData()._frecuency<<endl;
        cout<<"Character: "<<characters[characters.size()-1]->_element<<" Frecuency: "<<characters[characters.size()-1]->_frecuency<<endl;
    }
}

void PruebaArboles(){
    cout<<"Agregar Arbol Sin Padre: "<<endl;
    TreeElement* element=new TreeElement("1",56);    
    TreeNode* arbol=new TreeNode(*element);
    cout<<"Ver Elemenetos del Arbol sin Padres: "<<endl;
    cout<<"Elemento: "<<arbol->GetData()._element<<" Frecuencia: "<<arbol->GetData()._frecuency<<endl;

    cout<<"Añadir Arbol Con Padre el arbol anterior: "<<endl;
    element=new TreeElement("2", 35);
    TreeNode* arbol2=new TreeNode(*element, arbol);
    cout<<"Ver Elemenetos del Arbol Hijo: "<<endl;
    cout<<"Elemento: "<<arbol2->GetData()._element<<" Frecuencia: "<<arbol2->GetData()._frecuency<<endl;

    cout<<"Añadir Arbol Con Padre el arbol 1: "<<endl;
    element=new TreeElement("3", 36);
    TreeNode* arbol3=new TreeNode(*element, arbol);
    cout<<"Ver Elemenetos del Arbol Hijo 2: "<<endl;
    cout<<"Elemento: "<<arbol3->GetData()._element<<" Frecuencia: "<<arbol3->GetData()._frecuency<<endl;

    element=new TreeElement("4", 53);
    TreeNode* arbol4=new TreeNode(*element, arbol);
    cout<<"Ver Elemenetos del Arbol Hijo 3: "<<endl;
    cout<<"Elemento: "<<arbol4->GetData()._element<<" Frecuencia: "<<arbol4->GetData()._frecuency<<endl;

    cout<<"---Hijos de El Papi---"<<endl;
    for(int i=0; i<arbol->GetChildren().size(); i++){
        cout<<i<<") Elemento: "<<arbol->GetChildren()[i]->GetData()._element<<
                ", Frecuencia: "<<arbol->GetChildren()[i]->GetData()._frecuency<<endl;
    }

    cout<<"Setear al hijo 2: "<<endl;
    element=new TreeElement("1", 876);
    arbol3->SetData(*element);
    cout<<"Ver Elemenetos del Arbol Hijo 2 cambiado: "<<endl;
    cout<<"Elemento: "<<arbol3->GetData()._element<<" Frecuencia: "<<arbol3->GetData()._frecuency<<endl;


    for(int i=0; i<arbol->GetChildren().size(); i++){
        cout<<i<<") Elemento: "<<arbol->GetChildren()[i]->GetData()._element<<
                ", Frecuencia: "<<arbol->GetChildren()[i]->GetData()._frecuency<<endl;
    }
    cout<<"Comprobación Hojas"<<endl;
    cout<<"False "<<false<<" True "<<true<<endl;
    cout<<"Es Hoja? 1:"<<arbol2->IsLeaf()<<"Es Root? "<<arbol2->IsRoot()<<endl;
    cout<<"Es Hoja? 2:"<<arbol3->IsLeaf()<<"Es Root? "<<arbol3->IsRoot()<<endl;
    cout<<"Es Hoja? 3:"<<arbol4->IsLeaf()<<"Es Root? "<<arbol4->IsRoot()<<endl;

    cout<<"Comprobación Root: "<<endl;
    cout<<"False "<<false<<" True "<<true<<endl;
    cout<<"Es Hoja? Root:"<<arbol->IsLeaf()<<"Es Root? "<<arbol->IsRoot()<<endl;

    cout<<"Set parent 2:"<<endl;
    arbol2->SetParent(arbol3);
    cout<<"Hijos de 1:"<<endl;
    for(int i=0; i<arbol->GetChildren().size(); i++){
        cout<<i<<") Elemento: "<<arbol->GetChildren()[i]->GetData()._element<<
                ", Frecuencia: "<<arbol->GetChildren()[i]->GetData()._frecuency<<endl;
    }
    cout<<"Hijos de 3:"<<endl;
    for(int i=0; i<arbol3->GetChildren().size(); i++){
        cout<<i<<") Elemento: "<<arbol3->GetChildren()[i]->GetData()._element<<
                ", Frecuencia: "<<arbol3->GetChildren()[i]->GetData()._frecuency<<endl;
    }

    cout<<"Arbol 2 Agregar hijo:"<<endl;
    arbol2->AddChild(*new TreeElement("5",43));
    arbol2->AddChild(*new TreeElement("6",53));
    cout<<"Hijos de 2:"<<endl;
    for(int i=0; i<arbol2->GetChildren().size(); i++){
        cout<<i<<") Elemento: "<<arbol2->GetChildren()[i]->GetData()._element<<
                ", Frecuencia: "<<arbol2->GetChildren()[i]->GetData()._frecuency<<endl;
    }

    cout<<"Comprobación Hojas"<<endl;
    cout<<"False "<<false<<" True "<<true<<endl;
    cout<<"Es Hoja? 1:"<<arbol2->IsLeaf()<<"Es Root? "<<arbol2->IsRoot()<<endl;
    cout<<"Es Hoja? 2:"<<arbol3->IsLeaf()<<"Es Root? "<<arbol3->IsRoot()<<endl;
    cout<<"Es Hoja? 3:"<<arbol4->IsLeaf()<<"Es Root? "<<arbol4->IsRoot()<<endl;

    cout<<"Probar Destructor"<<endl;
    delete arbol3;
    cout<<"Eliminado"<<endl;
    delete arbol2;
    cout<<"Eliminado"<<endl;
    delete arbol;
    cout<<"Eliminado"<<endl;
}

void Huffman(vector <TreeElement*> characters){
}


