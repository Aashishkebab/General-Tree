#pragma once

#include <string>
#include "TreeNode.h"

#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL

class OrgTree{
private:
	TREENODEPTR root;
	unsigned int size;
public:
	OrgTree();
	~OrgTree();

	void addRoot(std::string title, std::string name);
	unsigned int getSize();
	unsigned int getSize(TreeNode * leftChild, unsigned int sum);
	TREENODEPTR getRoot();
	TREENODEPTR leftmostChild(TREENODEPTR node);
	TREENODEPTR rightSibling(TREENODEPTR node);
	void printSubTree(TREENODEPTR subTreeRoot);
	TREENODEPTR find(std::string title);
	TREENODEPTR find(std::string title, TreeNode * parent);
	bool read(std::string);
	void write(std::string);
	void hire(TREENODEPTR, std::string newTitle, std::string newName);
	bool fire(std::string formerTitle);
};
