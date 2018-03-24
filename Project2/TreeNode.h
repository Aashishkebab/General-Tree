#pragma once
#include <string>
class TreeNode{
private:
	std::string name;
	std::string title;
	//Aashish - I was thinking of using character arrays. And then I realized sanity was an option.

	TreeNode* leftmostChild;
	TreeNode* rightSibling;
	TreeNode* parent;

public:
	TreeNode();
	TreeNode(std::string title, std::string name);
	~TreeNode();

	void setLeftmostChild(TreeNode* node);
	void setRightSibling(TreeNode * node);
	void setParent(TreeNode * node);

	TreeNode* getLeftmostChild();
	TreeNode* getRightSibling();
	TreeNode * getParent();

	std::string getTitle();
	std::string getName();
};

