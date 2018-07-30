#include "treenode.h"

#include <sstream>
#include <iostream>
#include <string>
using std::ostream;
using std::istream;
using std::string;
using std::cerr;
using std::endl;

TreeNode::TreeNode(const TreeElement& data){
    _data=new TreeElement(data._element,data._frecuency);
    _parent=nullptr;
}

TreeNode::TreeNode(const TreeElement& data,TreeNode* parent){
    _parent=parent;
    _data=new TreeElement(data._element,data._frecuency);
    _parent->AddChild(this);
}

TreeNode::~TreeNode(){

}

vector<TreeNode*>& TreeNode::GetChildren(){
    return _children;
} 

void TreeNode::SetParent(TreeNode*){
    
}

void TreeNode::AddChild(const TreeElement& data){
    TreeNode* newChild=new TreeNode(data, this);
    if(_children.size()==0){
        _children.push_back(newChild);
    }
    else{
        TreeNode* temp=_children[_children.size()-1];
        _children[_children.size()-1]=newChild;
        _children.push_back(temp);
    }
}

void TreeNode::AddChild(TreeNode* child){
    if(_children.size()==0){
        _children.push_back(child);
    }else{
        TreeNode* temp=_children[_children.size()-1];
        _children[_children.size()-1]=child;
        _children.push_back(temp);
    }
}

TreeElement TreeNode::GetData()const{
    return *_data;
}

void TreeNode::SetData(const TreeElement&){

}

bool TreeNode::IsRoot()const{

}

bool TreeNode::IsLeaf()const{

}