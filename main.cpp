#include "treenode.h"
#include "treeelement.h"
#include <string.h>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

vector<string> GetText(char*[]);
vector <TreeElement*> GetFrecuencyVector(vector <string>);
bool SortTreeElements(TreeElement*, TreeElement*);
bool SortTreeNodes(TreeNode*, TreeNode*);
void PrintFrecuencyVector(vector <TreeElement*>);
vector <TreeNode*>GetTree(vector <TreeElement*>);
void Huffman(vector <TreeNode*>, vector <TreeElement*>);

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
    sort(characters.begin(), characters.end(), SortTreeElements);
    PrintFrecuencyVector(characters);
    tree=GetTree(characters);
    Huffman(tree,characters);
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
            }else if(int(character)>0){
                retVal.push_back(string(1,character));
            }
        }
        file.close();
    }
    retVal.pop_back();
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

bool SortTreeElements(TreeElement* treeElementA, TreeElement *treeElementB) { 
    if(treeElementA->_frecuency == treeElementB->_frecuency){
        return treeElementA->_element > treeElementB->_element;
    }else{
        return treeElementA->_frecuency > treeElementB->_frecuency;
    }
}

bool SortTreeNodes(TreeNode* treeNodeA, TreeNode *treeNodeB) { 
    return treeNodeA->GetData()._frecuency > treeNodeB->GetData()._frecuency;
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
    TreeNode* treeNode;
    for(int i=0; i<characters.size(); i++){
        treeNode=(new TreeNode(*characters[i]));
        treeVector.push_back(treeNode);
    }
    sort(treeVector.begin(), treeVector.end(), SortTreeNodes);
    while (treeVector.size()>1){
        stringstream nameTree;
        int frecuency;
        nameTree<<treeVector[treeVector.size()-1]->GetData()._element<<treeVector[treeVector.size()-2]->GetData()._element;
        frecuency=treeVector[treeVector.size()-1]->GetData()._frecuency+treeVector[treeVector.size()-2]->GetData()._frecuency;
        TreeElement* combinatedNode=new TreeElement(nameTree.str(),frecuency);
        treeNode=new TreeNode(*combinatedNode);
        treeNode->AddChild(treeVector[treeVector.size()-2]);
        treeNode->AddChild(treeVector[treeVector.size()-1]);
        treeVector.pop_back();
        treeVector.pop_back();
        treeVector.push_back(treeNode);
        sort(treeVector.begin(), treeVector.end(), SortTreeNodes);
        cout<<"Element: "<<treeNode->GetData()._element<<" Frecuency: "<<treeNode->GetData()._frecuency<<endl;
    }
    return treeVector;
}

void Huffman(vector <TreeNode*> treeNodes, vector <TreeElement*> characters){
    //sort(characters.begin(), characters.end(), SortByElement);
    TreeNode* tree=treeNodes[0];
    /*while(true){
        if(tree->IsLeaf()){
            break;
        }else{    
            if(characters[0]->_frecuency<=tree->GetData()._frecuency){
            tree=tree->GetChildren()[0];
            }else{

            }
        }
    }*/
    //PrintFrecuencyVector(characters);
    
}


