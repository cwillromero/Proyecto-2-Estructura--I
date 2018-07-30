#include "treenode.h"
#include "treeelement.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

string GetText(char*[]);
void PrintFrecuencies(vector <TreeElement*>&);
void PruebaArboles();
void Huffman(vector <TreeElement*>);

int main(int argc, char* argv[]){
    //PruebaArboles();
    string text;
    if(argc<2){
        cout<<"Parámetros Insuficientes."<<endl;
        return 0;
    }
    text=GetText(argv);
    if(text=="")
        return 0;
    cout<<text<<endl;
    vector <TreeElement*> characters;
    TreeElement* element=new TreeElement(string(1,text[0]));
    characters.push_back(element);
    string character;
    cout<<"Size Text"<<text.length()<<endl;
    for(int i=1; i<text.length(); i++){
        int cont=0;
        character=string(1,text[i]);
        for(int j=0; j<characters.size(); j++){
            if(characters[j]->_element==character){
                characters[j]->_frecuency++;
                cont++;
            }
            if(int(text[i])==32 && characters[j]->_element=="SP"){
                characters[j]->_frecuency++;
                cont++;
            }
            if(int(text[i])==10 && characters[j]->_element=="LF"){
                characters[j]->_frecuency++;
                cont++;
            }
            if(int(text[i])==13 && characters[j]->_element=="CR"){
                characters[j]->_frecuency++;
                cont++;
            }
        }
        if(cont==0){
            if(int(text[i])==32){
                element=new TreeElement("SP");
                characters.push_back(element);   
            }else if(int(text[i])==10){
                element=new TreeElement("LF");
                characters.push_back(element);   
            }else if(int(text[i])==13){
                element=new TreeElement("CR");
                characters.push_back(element);   
            }else{
                element=new TreeElement(character);
                characters.push_back(element);
            }
        }
    }

    //Ordenar 
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
    //Imprimir arreglo
    PrintFrecuencies(characters);
    vector<TreeNode*> trees;
    for(int i=0; i<characters.size(); i++){
        trees.push_back(new TreeNode(*characters[i]));
    }

    TreeNode* tree;
    while (characters.size()>1){
        stringstream name;
        int frecuency;
        TreeElement* node1=characters[characters.size()-1];
        TreeElement* node2=characters[characters.size()-2];
        name<<node1->_element<<node2->_element;
        frecuency=node1->_frecuency+node2->_frecuency;
        TreeElement* mix=new TreeElement(name.str(),frecuency);
        characters.pop_back();
        characters.pop_back();
        characters.push_back(mix);
        tree=new TreeNode(*mix);
        tree->AddChild(trees[trees.size()-2]);
        tree->AddChild(trees[trees.size()-1]);
        trees.pop_back();
        trees.pop_back();
        trees.push_back(tree);

        for(int i=0;i<characters.size();i++){
            for(int j=i+1;j<characters.size();j++){
                if(characters[i]->_frecuency<characters[j]->_frecuency){
                    TreeNode* tmp=trees[i];
                    TreeElement* temp=characters[i]; 
                    characters[i]=characters[j]; 
                    trees[i]=trees[j];
                    characters[j]=temp; 
                    trees[j]=tmp;
                }
            }
        }
        PrintFrecuencies(characters);
        cout<<"Element: "<<tree->GetData()._element<<" Frecuency: "<<tree->GetData()._frecuency<<endl;
    }
}

string GetText(char* argv[]){
    stringstream retVal;
    string line;
    fstream file;
    file.open (argv[1] , ios::in);
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file,line);
            retVal<<line;
            retVal<<endl;
        }
        file.close();
        return retVal.str();
    }else{
    cout<<"No se pudo abrir el archivo."<<endl;
    return "";
    }
}

void PrintFrecuencies(vector <TreeElement*>& characters){
    int cont=0;
    for(int j=0; j<characters.size(); j++){
        cont=cont+characters[j]->_frecuency;
        cout<<"Character: "<<characters[j]->_element<<"     Frecuency: "<<characters[j]->_frecuency<<endl;
    }
    cout<<cont<<endl;
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


