#pragma once

#include <string>
#include "TreeNode.h"

#define TREENODEPTR TreeNode*
#define TREENULLPTR NULL

class OrgTree{
private:
	TREENODEPTR root;

public:
	OrgTree();
	~OrgTree();

	void addRoot(std::string title, std::string name);
	unsigned int getSize();
	TREENODEPTR getRoot();
	TREENODEPTR leftmostChild(TREENODEPTR node);
	TREENODEPTR rightSibling(TREENODEPTR node);
	void printSubTree(TREENODEPTR subTreeRoot);
	TREENODEPTR find(std::string title);
	bool read(std::string);
	void write(std::string);
	void hire(TREENODEPTR, std::string newTitle, std::string newName);
	bool fire(std::string formerTitle);
};
