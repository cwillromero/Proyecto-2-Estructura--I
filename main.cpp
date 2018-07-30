#include "treenode.h"
#include "treeelement.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

string GetText(char*[]);
void PrintFrecuencies(vector <TreeElement*>&);
void PruebaArboles();

int main(int argc, char* argv[]){
    PruebaArboles();
    /*string text;
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
        }
    }
    
    //Imprimir arreglo
    PrintFrecuencies(characters);*/
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
    cout<<cont;
}

void PruebaArboles(){
    cout<<"Agregar Arbol Sin Padre: "<<endl;
    TreeElement* element=new TreeElement("ElPapi",56);    
    TreeNode* arbol=new TreeNode(*element);
    cout<<"Ver Elemenetos del Arbol sin Padres: "<<endl;
    cout<<"Elemento: "<<arbol->GetData()._element<<" Frecuencia: "<<arbol->GetData()._frecuency<<endl;
    cout<<"Añadir Arbol Con Padre el arbol anterior: "<<endl;
    element=new TreeElement("ElChamaco1", 3);
    TreeNode* arbol2=new TreeNode(*element, arbol);
    cout<<"Ver Elemenetos del Arbol Hijo: "<<endl;
    cout<<"Elemento: "<<arbol2->GetData()._element<<" Frecuencia: "<<arbol2->GetData()._frecuency<<endl;
    cout<<"Añadir Arbol Con Padre el arbol 1: "<<endl;
    element=new TreeElement("ElChamaco2", 3);
    TreeNode* arbol3=new TreeNode(*element, arbol);
    cout<<"Ver Elemenetos del Arbol Hijo 2: "<<endl;
    cout<<"Elemento: "<<arbol3->GetData()._element<<" Frecuencia: "<<arbol3->GetData()._frecuency<<endl;
    cout<<"---Hijos de El Papi---"<<endl;
    for(int i=0; i<arbol->GetChildren().size(); i++){
        cout<<i<<") Elemento: "<<arbol->GetChildren()[i]->GetData()._element<<
                ", Frecuencia: "<<arbol->GetChildren()[i]->GetData()._frecuency<<endl;
    }

}
