#include "stdafx.h"
#include "OrgTree.h"
#include <string>
#include <iostream>
#include <fstream>

static TREENODEPTR getRightmostItem(TREENODEPTR parent);
static void printChildren(TREENODEPTR leftChild, unsigned short numberOfTabs);

/*****************************************
Purpose:	Creates a tree object.
				Size is initialized to zero.
Time Complexity: Theta(1)
*****************************************/
OrgTree::OrgTree(){
	this->size = 0;
	this->root = nullptr;
}


OrgTree::~OrgTree(){
	//TODO - delete entire tree recursively.
	//Requirements do not state this is required,
	//so I ain't doin' it
}

/*****************************************
Purpose:	Adds a new root to the tree.
				If root already exists, it pushes it down below
				the new root created by this subroutine.
Time Complexity: Theta(1)
*****************************************/
void OrgTree::addRoot(std::string title, std::string name){
	this->size++;	//We have added a node, so we need to increase the size counter.
	if(!this->root == TREENULLPTR){	//If there is no root (aka root is null)
		this->root = new TreeNode(title, name);
	}
	else{	//If there is already a root
		TREENODEPTR temp = this->root;
		this->root = new TreeNode(title, name);
		this->root->setLeftmostChild(temp);	//Add the previous root as a child of the new root
	}
	return;
}

/*****************************************
Purpose:	Returns the number of tree nodes.
Time Complexity: Theta(1)
*****************************************/
unsigned int OrgTree::getSize(){
	return this->size;
}

/*****************************************
Purpose:	Returns pointer to the root of the tree
Time Complexity: Theta(1)
*****************************************/
TREENODEPTR OrgTree::getRoot(){
	return this->root;
}

/*****************************************
Purpose:	Returns pointer to leftmost child of node passed in
				Really it just calls the function on the node itself
Time Complexity: Theta(1)
*****************************************/
TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node){
	return node->getLeftmostChild();
}

/*****************************************
Purpose:	Returns pointer to right sibling of node parameter
Time Complexity: Theta(1)
*****************************************/
TREENODEPTR OrgTree::rightSibling(TREENODEPTR node){
	return node->getRightSibling();
}

/*****************************************
Purpose:	Traverses and prints the tree.
				It calls another function to do
				the work.
Inherited Time Complexity: Theta(n)
*****************************************/
void OrgTree::printSubTree(TREENODEPTR subTreeRoot){	//This ideally should be a static function
	if(!subTreeRoot){
		std::cout << "\nThere are no nodes..." << std::endl;
		return;
	}

	std::cout << std::endl << subTreeRoot->getTitle() << ": " << subTreeRoot->getName();

	printChildren(subTreeRoot->getLeftmostChild(), 1);	//Call the recursive print function with 1 tab space
}

/*****************************************
Purpose:	Prints all children of given object,
				with specified number of tabs
Time Complexity: Theta(n)
*****************************************/
static void printChildren(TREENODEPTR leftChild, unsigned short numberOfTabs){	//This should also be a static function
	std::cout << std::endl;

	TREENODEPTR temp = leftChild;

	while(temp){
		for(unsigned short i = 0; i < numberOfTabs; i++){	//Print tab a certain number of times
			std::cout << "\t";
		}
		std::cout << temp->getTitle() << ": " << temp->getName();

		if(temp->getLeftmostChild()){	//If there is a child, recurse on that child
			printChildren(temp->getLeftmostChild(), numberOfTabs + 1);
		}
		else{
			std::cout << "\n";
		}

		temp = temp->getRightSibling();	//Repeat this loop on the next sibling
	}
}

/*****************************************
Purpose:	Returns pointer to node with given title.
				Returns the first node it finds.
Inherited Time Complexity:	Inherits from find(string, TREENODEPTR)
	Worst Case time complexity:	Theta(n)
	Best Case time complexity:		Theta(1)
*****************************************/
TREENODEPTR OrgTree::find(std::string title){
	return find(title, this->root);
}

/*****************************************
Purpose:	Returns pointer to node with given title.
				Starts search at given parent.
Worst Case time complexity:	Theta(n)
Best Case time complexity:		Theta(1)
*****************************************/
TREENODEPTR OrgTree::find(std::string title, TREENODEPTR parent){
	TREENODEPTR temp = parent;

	while(temp){
		if(temp->getTitle() == title){	//Iterate through all top level items
			return temp;
		}
		temp = temp->getRightSibling();
	}

	temp = parent;
	TREENODEPTR result;
	while(temp){
		if(temp->getLeftmostChild()){	//If children exist, recursively perform this subroutine on these children
			result = find(title, temp->getLeftmostChild());
			if(result){	//Return only of the result of the recursion actually exists, otherwise keep going
				return result;
			}
		}
		temp = temp->getRightSibling();
	}

	return TREENULLPTR;	//Outside function should handle this
}

/*****************************************
Purpose:	Creates Tree from given file
Time complexity: Theta(n)
*****************************************/
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
}	//I didn't write this function. It was given by Raymer. I did modify it slightly.

/*****************************************
Purpose:	Reads tree from the file "filename"
Inherited Time complexity: Theta(n)
*****************************************/
bool OrgTree::read(std::string filename){
	std::ifstream file;
	file.open(filename);
	if(!file){
		return false;
	}
	this->root = readTree(file);

	if(this->root){
		return true;
	}
	else{
		return false;
	}
}

/*****************************************
Purpose:	Writes tree to file starting at given parent
Time complexity: Theta(n)
*****************************************/
static void writeTheTree(std::ofstream& file, TREENODEPTR parent){
	TREENODEPTR temp = parent;

	while(temp){
		file << temp->getTitle() << ", " << temp->getName() << "\n";
		if(temp->getLeftmostChild()){	//If the node has a child, recursively perform this function on that child
			writeTheTree(file, temp->getLeftmostChild());
		}
		temp = temp->getRightSibling();
		file << ")" << "\n";
	}
}

/*****************************************
Purpose:	Writes tree to file "filename"
Time complexity: Theta(n)
*****************************************/
void OrgTree::write(std::string filename){
	std::ofstream file;
	file.open(filename);

	writeTheTree(file, this->root);
}

/*****************************************
Purpose:	Adds node as child of given parent,
				with given title and name.
Worst case time complexity: Theta(n)
Best Case time complexity: Theta(1)
*****************************************/
void OrgTree::hire(TREENODEPTR parent, std::string newTitle, std::string newName){
	if(!parent){
		//std::cout << "\nCould not hire " << newName << std::endl;
		throw "No parent node";
		return;
	}

	TREENODEPTR temp = parent->getLeftmostChild();
	if(temp){
		//while(temp->getRightSibling()){	//Find the rightmost item
		//	temp = temp->getRightSibling();
		//}
		try{
			temp = getRightmostItem(parent);
		}
		catch(std::string e){
			std::cout << "\nCouldn't hire " << newName << std::endl;
			return;
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

/*****************************************
Purpose:	Deletes node with given title,
				then shifts other nodes around
				to ensure tree continuity
Inherited time complexity:	Inherits from find(string) and
												inherits from (getRightmostItem(TREENODEPTR))
Worst case time complexity: Theta(n)
Best case time complexity: Theta(1)
*****************************************/
bool OrgTree::fire(std::string formerTitle){
	if(formerTitle == this->root->getTitle()){
		return false;
	}

	TREENODEPTR itemToFire = find(formerTitle);
	if(!itemToFire){
		return false;
	}

	TREENODEPTR leftSibling = itemToFire->getParent()->getLeftmostChild();	//To find left sibling of itemToFire

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

/*****************************************
Purpose:	Returns pointer to rightmost child
				of given parent
Time complexity: Theta(n)
*****************************************/
static TREENODEPTR getRightmostItem(TREENODEPTR parent){
	if(!parent){
		throw "No parent here";
		return nullptr;
	}

	TREENODEPTR temp = parent->getLeftmostChild();
	if(!temp){
		return TREENULLPTR;
	}
	while(temp->getRightSibling()){
		temp = temp->getRightSibling();
	}
	return temp;
}