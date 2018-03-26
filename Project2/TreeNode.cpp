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

void TreeNode::setParent(TreeNode* node){
	this->parent = node;
}

TreeNode* TreeNode::getLeftmostChild(){
	return this->leftmostChild;
}

TreeNode* TreeNode::getRightSibling(){
	return this->rightSibling;
}

TreeNode* TreeNode::getParent(){
	return this->parent;
}

std::string TreeNode::getTitle(){
	return this->title;
}

std::string TreeNode::getName(){
	return this->name;
}

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
