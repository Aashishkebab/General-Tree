#include "stdafx.h"
#include "OrgTree.h"
#include <string>
#include <iostream>
#include <fstream>

static TreeNode* getRightmostItem(TreeNode* parent);


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

void OrgTree::printSubTree(TREENODEPTR subTreeRoot){	//This ideally should be a static function
	TreeNode* current = subTreeRoot;
	std::cout << std::endl << subTreeRoot->getTitle() << ": " << subTreeRoot->getName();

	printChildren(subTreeRoot->getLeftmostChild(), 1);
}

void OrgTree::printChildren(TREENODEPTR leftChild, unsigned short numberOfTabs){	//This should also be a static function
	std::cout << std::endl;

	TreeNode* temp = leftChild;

	while(temp){
		for(unsigned short i = 0; i < numberOfTabs; i++){
			std::cout << "\t";
		}
		std::cout << temp->getTitle() << ": " << temp->getName();

		if(temp->getLeftmostChild()){
			printChildren(temp->getLeftmostChild(), numberOfTabs + 1);
		}
		else{
			std::cout << "\n";
		}

		temp = temp->getRightSibling();
	}
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
	TreeNode* temp = parent;

	while(temp){
		if(temp->getTitle() == title){
			return temp;
		}

		temp = temp->getRightSibling();
	}

	temp = parent;
	TreeNode* result;
	while(temp){
		if(temp->getLeftmostChild()){
			result = find(title, temp->getLeftmostChild());
			if(result){
				return result;
			}
		}
		temp = temp->getRightSibling();
	}

	return nullptr;	//Outside function should handle this
}


TREENODEPTR readTree(std::ifstream &inFile){	//Causes memory leak if previous tree existed
	std::string newTitle, newName, junk;
	if(inFile.peek() == ')')
		return nullptr;
	std::getline(inFile, newTitle, ','); 
	std::getline(inFile, newName);
	TREENODEPTR subroot = new TreeNode(newTitle, newName);
	while(inFile.peek() != ')'){
		subroot->addChild(readTree(inFile));
	}
	getline(inFile, junk); // Read the ‘)’ char
	return subroot;
}


bool OrgTree::read(std::string filename){
	std::ifstream inFile;
	inFile.open(filename);
	if(!inFile){
		return false;
	}
	this->root = readTree(inFile);

	if(this->root){
		return true;
	}
	else{
		return false;
	}
}

void OrgTree::write(std::string){

}

void OrgTree::hire(TREENODEPTR parent, std::string newTitle, std::string newName){
	TREENODEPTR temp = parent->getLeftmostChild();
	if(temp){
		while(temp->getRightSibling()){
			temp = temp->getRightSibling();
		}
		temp->setRightSibling(new TreeNode(newTitle, newName));
		temp->getRightSibling()->setParent(parent);
	}
	else{
		parent->setLeftmostChild(new TreeNode(newTitle, newName));
		parent->getLeftmostChild()->setParent(parent);
	}

	this->size++;
}

bool OrgTree::fire(std::string formerTitle){
	if(formerTitle == this->root->getTitle()){
		return false;
	}

	TreeNode* itemToFire = find(formerTitle);
	if(!itemToFire){
		return false;
	}

	TreeNode* leftSibling = itemToFire->getParent()->getLeftmostChild();	//To find left sibling of itemToFire

	if(leftSibling != itemToFire){	//If item to fire is not leftmost child of its parent
		while(leftSibling->getRightSibling() != itemToFire){
			leftSibling = leftSibling->getRightSibling();
		}
		leftSibling->setRightSibling(itemToFire->getRightSibling());
	}
	else{	//If item to fire is leftmost child of its parent
		itemToFire->getParent()->setLeftmostChild(itemToFire->getRightSibling());
	}

	getRightmostItem(itemToFire->getParent())->setRightSibling(itemToFire->getLeftmostChild());

	delete itemToFire;

	return true;
}

static TreeNode* getRightmostItem(TreeNode* parent){
	if(!parent){
		throw "No parent here";
	}

	TreeNode* temp = parent->getLeftmostChild();
	while(temp->getRightSibling()){
		temp = temp->getRightSibling();
	}
	return temp;
}