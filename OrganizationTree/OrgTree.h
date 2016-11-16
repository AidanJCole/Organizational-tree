// By Aidan Cole

#pragma once
#include <string>
#define TREENODEPTR TreeNode*
#define TREENODENULL NULL
#include <fstream>

struct TreeNode;

struct TreeNode{
	std::string title;
	std::string name;
	TreeNode* child = NULL;
	TreeNode* right = NULL;
 };


class OrgTree
{
public:
	
	OrgTree();
	~OrgTree();
	void OrgTree::addRoot(std::string title, std::string name);
	int OrgTree::getSize();
	TreeNode* OrgTree::getRoot();
	TreeNode* OrgTree::leftmostChild(TreeNode* node);
	TreeNode* OrgTree::rightSibling(TreeNode* node);
	void OrgTree::printSubTree(TreeNode* subTreeRoot);
	TREENODEPTR OrgTree::find(std::string title);
	void OrgTree::hire(TreeNode* boss, std::string newTitle, std::string name);
	bool OrgTree::fire(std::string formerTitle);
	bool OrgTree::read(std::string filename);
	void OrgTree::write(std::string filename);
private:
	void OrgTree::recurPrintSubTree(TreeNode* subRoot, int depth);
	TreeNode* OrgTree::recurFind(TreeNode* subRoot, std::string title);
	bool OrgTree::recurFire(TreeNode* root,TreeNode* current, std::string title);
	void OrgTree::helpDel(TreeNode* parent, TreeNode* deleted);
	int memberNumber = 0;
	struct TreeNode* root = NULL;
	bool OrgTree::recurRead(std::ifstream& myFile, TreeNode* parent);
	void OrgTree::recurwrite(std::ofstream& fileName, TreeNode* root);
	void OrgTree::deleteTree(TreeNode* current);
};

