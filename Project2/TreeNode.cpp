#include "stdafx.h"
#include "TreeNode.h"
#include <string>


TreeNode::TreeNode(){}

/*****************************
Purpose:	Creates a TreeNode with given title and name.
Time Complexity:	Theta(1)
****************************/
TreeNode::TreeNode(std::string title, std::string name){
	this->name = name;
	this->title = title;
}


TreeNode::~TreeNode(){}

/*****************************
Purpose:	Sets the leftmost child pointer to node passed in
Time Complexity:	Theta(1)
****************************/
void TreeNode::setLeftmostChild(TreeNode* node){
	this->leftmostChild = node;
}

/*****************************
Purpose:	Sets the right sibling pointer to node passed in
Time Complexity:	Theta(1)
****************************/
void TreeNode::setRightSibling(TreeNode* node){
	this->rightSibling = node;
}

/*****************************
Purpose:	Sets the parent pointer to node passed in
Time Complexity:	Theta(1)
****************************/
void TreeNode::setParent(TreeNode* node){
	this->parent = node;
}

/*****************************
Purpose:	Returns a pointer to the leftmost child
Time Complexity:	Theta(1)
****************************/
TreeNode* TreeNode::getLeftmostChild(){
	return this->leftmostChild;
}


/*****************************
Purpose:	Returns a pointer to the right sibling of this node
Time Complexity:	Theta(1)
****************************/
TreeNode* TreeNode::getRightSibling(){
	return this->rightSibling;
}

/*****************************
Purpose:	Returns a pointer to the parent of this node
Time Complexity:	Theta(1)
****************************/
TreeNode* TreeNode::getParent(){
	return this->parent;
}

/*****************************
Purpose:	Returns the "title" of this node
Time Complexity:	Theta(1)
****************************/
std::string TreeNode::getTitle(){
	return this->title;
}

/*****************************
Purpose:	Returns the "name" of this node
Time Complexity:	Theta(1)
****************************/
std::string TreeNode::getName(){
	return this->name;
}

/*************************************************
Purpose:	Adds a node as a child
				of the current parent as
				far to the right as it can.
Worst case time complexity:	Theta(n)
Best case time complexity:		Theta(1)
**************************************************/
void TreeNode::addChild(TreeNode* theChild){
	if(this->leftmostChild){
		TreeNode* temp = this->leftmostChild;

		while(temp->rightSibling){
			temp = temp->rightSibling;
		}
		temp->rightSibling = theChild;
	}
	else{
		this->leftmostChild = theChild;
	}
}
