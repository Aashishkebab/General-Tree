#include "stdafx.h"
#include "TreeNode.h"
#include <string>


TreeNode::TreeNode(){}

TreeNode::TreeNode(std::string title, std::string name){
	this->name = name;
	this->title = title;
}


TreeNode::~TreeNode(){}

void TreeNode::setLeftmostChild(TreeNode* node){
	this->leftmostChild = node;
}

void TreeNode::setRightSibling(TreeNode* node){
	this->rightSibling = node;
}

TreeNode* TreeNode::getLeftmostChild(){
	return this->leftmostChild;
}

TreeNode* TreeNode::getRightSibling(){
	return this->rightSibling;
}

std::string TreeNode::getTitle(){
	return this->title;
}

std::string TreeNode::getName(){
	return this->name;
}
