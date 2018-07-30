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
    _parent->_children.push_back(this);
}

TreeNode::~TreeNode(){

}

vector<TreeNode*>& TreeNode::GetChildren()const{
    /*vector<TreeNode*> retval;
    for(int i=0; i<_children.size(); i++){
        retval.push_back(_children[i]);
    }
    return retval;*/
} 

void TreeNode::SetParent(TreeNode*){
    
}

void TreeNode::AddChild(const TreeElement& data){
    TreeNode* newChild=new TreeNode(data, this);
    TreeNode* temp=_children[_children.size()-1];
    _children[_children.size()-1]=newChild;
    _children.push_back(temp);
}

void TreeNode::AddChild(TreeNode* child){
    TreeNode* temp=_children[_children.size()-1];
    _children[_children.size()-1]=child;
    _children.push_back(temp);
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