#include "stdafx.h"
#include "OrgTree.h"
#include <string>
#include <iostream>


OrgTree::OrgTree(){
	this->size = 0;
	this->root = nullptr;
}

OrgTree::~OrgTree(){
	delete this->root;
}

void OrgTree::addRoot(std::string title, std::string name){
	this->size++;
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
	return this->size;
	//return getSize(this->root, 0);
}

/*******
This function recursively counts each node in the tree.
It is not used.
*******/
unsigned int OrgTree::getSize(TreeNode* child, unsigned int sum){
	if(child->getRightSibling()){
		sum += getSize(child->getRightSibling(), sum);
	}

	TreeNode* temp = child;
	while(temp->getLeftmostChild()){
		temp = temp->getLeftmostChild();
		if(temp->getRightSibling()){
			sum += getSize(temp, sum);
		}
		sum++;
	}
	return sum;
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

/********************************
This function will recurse to the
bottom of the tree. Then it will
iterate through all the right siblings
*********************************/
TREENODEPTR OrgTree::find(std::string title, TreeNode* parent){
	if(parent->getLeftmostChild()){
		return find(title, parent->getLeftmostChild());	//If this child has children, recurse through them
	}

	TreeNode* temp = parent;

	while(temp->getRightSibling()){	//If there exists a right sibling t this item
		temp = temp->getRightSibling();	//Iterate the temp pointer to the right sibling
		if(temp->getLeftmostChild()){	//Check if the next sibling has children
			return find(title, temp);	//If this sibling has children, recurse through them
		}
		if(temp->getTitle() == title){
			return temp;
		}
	}
	return nullptr;	//Outside function should handle this
}

bool OrgTree::read(std::string){
	return false;
}

void OrgTree::write(std::string){

}

void OrgTree::hire(TREENODEPTR parent, std::string newTitle, std::string newName){
	TREENODEPTR temp = parent->getLeftmostChild();
	while(temp->getRightSibling()){
		temp = temp->getRightSibling();
	}
	temp->setRightSibling(new TreeNode(newTitle, newName));
	temp->getRightSibling()->setParent(parent);

	this->size++;
}

bool OrgTree::fire(std::string formerTitle){
	TreeNode* itemToFire = find(formerTitle);
	TreeNode* leftSibling = itemToFire->getParent()->getLeftmostChild();	//To find left sibling of itemToFire

	if(itemToFire->getParent()->getLeftmostChild() != itemToFire){	//If item to fire is not leftmost child of its parent
		while(leftSibling->getRightSibling() != itemToFire){
			leftSibling = leftSibling->getRightSibling();
		}
		leftSibling->setRightSibling(itemToFire->getRightSibling());
	}
	else{	//If item to fire is not leftmost child of its parent
		itemToFire->getParent()->setLeftmostChild(itemToFire->getRightSibling());
	}

	if(itemToFire->getLeftmostChild()){
		TreeNode* child = itemToFire->getLeftmostChild();
		while(child){
			child->setParent(itemToFire->getParent());
			child = child->getRightSibling();
		}
	}

	delete itemToFire;

	return false;
}
