#pragma once

#include <string>
#include "TreeNode.h"

#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL


/*********************************************
Space complexity:
	Node size:	string x 2, pointer x 3
	Tree size:		pointer x 1, unsigned int x 1
*********************************************/
class OrgTree{
private:
	TREENODEPTR root;	//Pointer to root of tree
	unsigned int size;			//Counter that tracks how large the tree is
public:
	OrgTree();
	~OrgTree();

	void addRoot(std::string title, std::string name);
	unsigned int getSize();
	unsigned int getSize(TREENODEPTR leftChild, unsigned int sum);
	TREENODEPTR getRoot();
	TREENODEPTR leftmostChild(TREENODEPTR node);
	TREENODEPTR rightSibling(TREENODEPTR node);
	void printSubTree(TREENODEPTR subTreeRoot);
	TREENODEPTR find(std::string title);
	TREENODEPTR find(std::string title, TREENODEPTR parent);
	bool read(std::string);
	void write(std::string);
	void hire(TREENODEPTR, std::string newTitle, std::string newName);
	bool fire(std::string formerTitle);
};
