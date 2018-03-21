#include "stdafx.h"
#include "OrgTree.h"
#include <string>
#include <iostream>


OrgTree::OrgTree(){}

OrgTree::~OrgTree(){
	delete this->root;
}

void OrgTree::addRoot(std::string title, std::string name){
	if(!this->root == TREENULLPTR){
		this->root = new TreeNode(title, name);
	}
	else{
		TreeNode* temp = this->root;
		this->root = new TreeNode(title, name);
		this->root->setLeftmostChild(temp);
	}
	return;
}

unsigned int OrgTree::getSize(){
	return getSize(this->root, 0);
}

unsigned int OrgTree::getSize(TreeNode* child, unsigned int sum){
	if(child->getRightSibling()){
		sum += getSize(child->getRightSibling, sum);
	}

	TreeNode* temp = child;
	while(temp->getLeftmostChild()){
		temp = temp->getLeftmostChild();
		if(temp->getRightSibling()){
			sum += getSize(temp, sum);
		}
		sum++;
	}
}

TREENODEPTR OrgTree::getRoot(){
	return this->root;
}

TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node){
	return node->getLeftmostChild();
}

TREENODEPTR OrgTree::rightSibling(TREENODEPTR node){
	return node->getRightSibling();
}

void OrgTree::printSubTree(TREENODEPTR subTreeRoot){
	std::cout << "Printamafying";
}

TREENODEPTR OrgTree::find(std::string title){
	return find(title, this->root);
}

TREENODEPTR OrgTree::find(std::string title, TreeNode* parent){
	if(parent->getLeftmostChild()){
		return find(title, parent->getLeftmostChild());
	}

	TreeNode* temp = parent;

	while(temp->getRightSibling()){
		temp = temp->getRightSibling();
		if(temp->getLeftmostChild()){
			return find(title, temp);
		}
		if(temp->getTitle() == title){
			return temp;
		}
	}
	return nullptr;
}

bool OrgTree::read(std::string){
	return false;
}

void OrgTree::write(std::string){

}

void OrgTree::hire(TREENODEPTR parent, std::string newTitle, std::string newName){
	//TODO - Add to last child of TREENODEPTR
	TREENODEPTR temp = parent->getLeftmostChild();
	while(temp->getRightSibling()){
		temp = temp->getRightSibling();
	}
	temp->setRightSibling(temp);
}

bool OrgTree::fire(std::string formerTitle){
	return false;
}
