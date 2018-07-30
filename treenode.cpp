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
    if(_children.size()==0){
        for(int i=0; i<_children.size(); i++){
            delete _children[i];
        }
    }
    _children.clear();
    if(_data!=nullptr)
        delete _data;
}

vector<TreeNode*>& TreeNode::GetChildren(){
    return _children;
} 

void TreeNode::SetParent(TreeNode* parent){
    for(int i=0; i<_parent->_children.size(); i++){
        if(_parent->_children[i]==this){
            for(int j=i; j<_parent->_children.size()-1; j++){
                _parent->_children[j]=_parent->_children[j+1];
            }
            _parent->_children[_parent->_children.size()-1]=nullptr;
        }
    }
    _parent->_children.pop_back();
    _parent=parent;
    _parent->AddChild(this);
}

void TreeNode::AddChild(const TreeElement& data){
    TreeNode* newChild=new TreeNode(data, this);
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

void TreeNode::SetData(const TreeElement& data){
    _data=new TreeElement(data._element,data._frecuency);
}

bool TreeNode::IsRoot()const{
    if(_parent==nullptr)
        return true;
    else
        return false;
}

bool TreeNode::IsLeaf()const{
    if(_children.size()==0)
        return true;
    else
        return false;
}