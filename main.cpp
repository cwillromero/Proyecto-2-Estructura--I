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
void PrintFrecuencyVector(vector <TreeElement*>);
vector <TreeNode*>GetTree(vector <TreeElement*>);
string Huffman(TreeNode*,TreeElement*);

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
    //PrintFrecuencyVector(characters);
    tree=GetTree(characters);
    //cout<<"***Element: "<<tree[0]->GetData()._element<<" Frecuency: "<<tree[0]->GetData()._frecuency<<endl;
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
}

vector<string> GetText(char* argv[]){
    vector <string> retVal;
    char character;
    fstream file;
    file.open (argv[1] , ios::in);
    if (file.is_open()) {
        while (file.get(character)) {
            /*if(int(character)==32){
                retVal.push_back("SP");
            }else if(int(character)==10){
                retVal.push_back("LF");
            }else if(int(character)==13){
                retVal.push_back("CR");*/
            if(int(character)>0){
                retVal.push_back(string(1,character));
            }
        }
        file.close();
    }
    //retVal.pop_back();
    return retVal;
}

vector<TreeElement*> GetFrecuencyVector(vector<string> text){
    vector <TreeElement*> characters;
    TreeElement* element=new TreeElement(text[0]);
    characters.push_back(element);
    string character;
    //cout<<"Size Text"<<text.size()<<endl;
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
        return treeElementA->_element > treeElementB->_element ;
    }else{
        return treeElementA->_frecuency > treeElementB->_frecuency;
    }
}

bool SortTreeNodes(TreeNode* treeNodeA, TreeNode *treeNodeB) { 
    if(treeNodeA->GetData()._frecuency == treeNodeB->GetData()._frecuency){
        return treeNodeA->GetData()._element > treeNodeB->GetData()._element;
    }else{
        return treeNodeA->GetData()._frecuency > treeNodeB->GetData()._frecuency;
    }
}

void PrintFrecuencyVector(vector <TreeElement*> characters){
    int cont=0;
    for(int j=0; j<characters.size(); j++){
        //cont=cont+characters[j]->_frecuency;
        //cout<<"{element: "<<characters[j]->_element<<", frecuency: "<<characters[j]->_frecuency<<"}"<<endl;
    }
    //cout<<cont<<endl;
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
        //cout<<"Element: "<<treeNode->GetData()._element<<" Frecuency: "<<treeNode->GetData()._frecuency<<endl;
    }
    return treeVector;
}

string Huffman(TreeNode* treeNode, TreeElement* treeElement){
    TreeNode* tree=treeNode;
    vector< TreeNode*> stack;
    stringstream code;
    //int cont=0;
   while(!tree->IsLeaf()){
        //cout<<"**"<<tree->GetData()._element<<endl;
        //usleep(1000000);
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

       /* if(!tree->IsLeaf()){
            stack.push_back(tree);
            //cout<<"**"<<tree->GetData()._element<<endl;
            tree=tree->GetChildren()[0];
            //usleep(1000000);
            code.push_back("1");
        }else{
            //cout<<"**"<<tree->GetData()._element<<endl;
            //usleep(1000000);
            if(tree->GetData()._element==treeElement->_element){
                stringstream _code;
                for(int i=0; i<code.size();i++){
                    _code<<code[i];
                }
                return _code.str();
            }else{
                code.pop_back();
                tree=stack[stack.size()-1];
                tree=tree->GetChildren()[1];
                code.push_back("0");
                //cout<<"**"<<tree->GetData()._element<<endl;
                //usleep(1000000);
            }
        }
        if(stack[stack.size()-1]->GetChildren()[1]->GetData()._element == tree->GetData()._element){
            if(tree->IsLeaf()){
                if(tree->GetData()._element==treeElement->_element){
                stringstream _code;
                for(int i=0; i<code.size();i++){
                    _code<<code[i];
                }
                return _code.str();
                }
                tree=stack[stack.size()-1];
                tree->MakeLeaf();
                stack.pop_back();
                code.pop_back();
            }
        }*/
    }
}



