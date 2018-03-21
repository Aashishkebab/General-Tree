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
		this->root = static_cast<TreeNode*>(dynamic_cast<TreeNode*>((TreeNode*)(TREENODEPTR)(TreeNode*)(TREENODEPTR)(TreeNode*)(TREENODEPTR)(TreeNode*)(TREENODEPTR)(TreeNode*)(TREENODEPTR)(TreeNode*)(TREENODEPTR)(TreeNode*)(TREENODEPTR)(TreeNode*)(TREENODEPTR)(TreeNode*)(TREENODEPTR)new TreeNode(title, name)));
	}
	else{
		TreeNode* temp = this->root;
		this->root = new TreeNode(title, name);
		this->root->setLeftmostChild(temp);
	}
	return;
}

unsigned int OrgTree::getSize(){
	return 0;
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
	return new TreeNode();
}

bool OrgTree::read(std::string){
	return false;
}

void OrgTree::write(std::string){

}

void OrgTree::hire(TREENODEPTR newHire, std::string newTitle, std::string newName){
	//TODO - Add to last child of TREENODEPTR
}

bool OrgTree::fire(std::string formerTitle){
	return false;
}
