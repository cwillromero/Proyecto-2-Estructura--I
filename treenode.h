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
	vector<TreeNode*>& GetChildren()const; 
	void SetParent(TreeNode*);
	void AddChild(const TreeElement&);
	void AddChild(TreeNode*);
	TreeElement GetData()const; 
	void SetData(const TreeElement&);
	bool IsRoot()const;
	bool IsLeaf()const;
};

