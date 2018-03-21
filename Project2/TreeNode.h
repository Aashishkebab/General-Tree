#pragma once
#include <string>
class TreeNode{
private:
	std::string name;
	std::string title;
	//Aashish - I was thinking of using character arrays. And then I realized sanity was an option.

	TreeNode* leftmostChild;
	TreeNode* rightSibling;

public:
	TreeNode();
	TreeNode(std::string title, std::string name);
	~TreeNode();

	void setLeftmostChild(TreeNode* node);
	TreeNode* getLeftmostChild();
	TreeNode* getRightSibling();
};

