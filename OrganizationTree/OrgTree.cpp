//By Aidan cole
#include "stdafx.h"
#include "OrgTree.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


OrgTree::OrgTree()
{

}

/*
	Runs in O(n) time
*/
OrgTree::~OrgTree()
{
	deleteTree(root);
	root = NULL;
}

/*
	Helper for the destructor
*/
void OrgTree::deleteTree(TreeNode* current) {
	if (current == NULL) {
		return;
	}
	deleteTree(current->child);
	deleteTree(current->right);
	delete current;
}

/*
	Creates a root node for the tree. If the tree already has a root, the entire tree becomes a subtree of the new root
	The theta runtime is O(1).
*/
void OrgTree::addRoot(string title, string name) 
{
	memberNumber++;
	if (root == NULL) {
		root = new TreeNode();
		root->name = name;
		root->title = title;
	}
	else 
	{
		TreeNode* temp = new TreeNode();
		temp->name = name;
		temp->title = title;
		temp->child = root;
		root = temp;
	}
}

/*
	Returns the size of the tree.
	Runs in O(1) time.
*/
int OrgTree::getSize() {
	return memberNumber;
}

/*
	Returns the root of the tree.
	Runs in O(1) time.
*/
TreeNode* OrgTree::getRoot() {
	return root;
}

/*
	Returns the leftmost child of the node.
	Runs in O(1) time.
*/
TreeNode* OrgTree::leftmostChild(TreeNode* node) {
	if (node == NULL) {
		return NULL;
	}
	return node->child;
}

/*
	Returns the right sibling of the node.
	Runs in O(1) time.
*/
TreeNode* OrgTree::rightSibling(TreeNode* node) {
	if (node == NULL) {
		return NULL;
	}
	return node->right;
}

/*
	Prints out the members of the tree, with tabs corresponding to nesting levels.
	Runs in O(N) time
*/
void OrgTree::printSubTree(TreeNode* subTreeRoot) 
{
	recurPrintSubTree(subTreeRoot, 0);
}

/*
Prints out the members of the tree, with tabs corresponding to nesting levels.
Runs in O(N) time
*/
void OrgTree::recurPrintSubTree(TreeNode* subRoot, int depth) {
	if (subRoot == NULL) {
		return;
	}
	for (int i = 0; i < depth; i++)
	{
		cout << "\t";
	}
	cout << subRoot->title << ": " << subRoot->name << endl;
	recurPrintSubTree(subRoot->child, depth + 1);
	recurPrintSubTree(subRoot->right, depth);
}

/*
Returns a reference to the node with the given reference
Runs in O(1) time.
*/
TREENODEPTR OrgTree::find(string title) {
	return recurFind(root, title);
}

TreeNode* OrgTree::recurFind(TreeNode* subRoot, string title) {
	if (subRoot->title==title || subRoot == NULL) {
		return subRoot;
	}
	TreeNode* temp = recurFind(subRoot->child, title);
	if (temp == NULL) {
		return recurFind(subRoot->right, title);
	}
	return temp;
}

/*
Add a child as the last child of the provided node.
Runs in O(N) time, with N as the number of child nodes of the provided node.
*/
void OrgTree::hire(TreeNode* boss, std::string newTitle, std::string name) {
	if (boss == NULL) {
		return;
	}
	TreeNode* temp = new TreeNode();
	temp->title = newTitle;
	temp->name = name;
	if (boss->child == NULL) {
		boss->child = temp;
	}
	else {
		TreeNode* temper = boss->child;
		while (temper->right != NULL) {
			temper = temper->right;
		}
		temper->right = temp;
	}
}

/*
	Fires an employee with a given title
	Runs in O(n) time
*/
bool OrgTree::fire(string formerTitle) {
	if (root->title == formerTitle||root == NULL) {
		return false;
	}
	return recurFire(root, root->child, formerTitle);
}

/*
	Helper function for fire function,
	Runs in O(n)
*/
bool OrgTree::recurFire(TreeNode* root, TreeNode* current, string title) {
	if (current == NULL || root == NULL) {
		return false;
	}
	else if (current->title==title) {
		TreeNode* rightMost = root->child;
		while (rightMost->right != NULL) {
			rightMost = rightMost->right;
		}
		rightMost->right = current->child;
		current->child = NULL;
		helpDel(root, current);
		return true;
	}
	else {
		return recurFire(root, current->right, title) || recurFire(root, current->child, title);
	}
}

/*
	Helper function for recurFire
	Runs in O(m), where m is the number of child nodes of parent
*/
void OrgTree::helpDel(TreeNode* parent, TreeNode* deleted) {
	memberNumber--;
	if (deleted == parent->child) {
		parent->child = deleted->right;
		delete deleted;
	}
	else {
		TreeNode* toBeDeleted = parent->child->right;
		TreeNode* before = parent->child;
		while (toBeDeleted != deleted) {
			before = toBeDeleted;
			toBeDeleted = toBeDeleted->right;
		}
		before->right = toBeDeleted->right;
		delete toBeDeleted;
	}
}

/*
	Reads a tree from a file.
	Runs in O(n) time
*/
bool OrgTree::read(std::string filename) {
	ifstream myFile(filename);
	if (!myFile.good()) {
		return false;
	}
	string line;
	getline(myFile, line);
	if (line == ")") {
		return false;
	}
	if (line.find(", ") == -1) {
		return false;
	}
	else {
		TreeNode* temp = new TreeNode();
		temp->title = line.substr(0, line.find(", "));
		temp->name = line.substr(line.find(", ") + 2, line.size() - line.find(", ") - 2);
		root = temp;
		return recurRead(myFile, root);
	}
	
}
bool OrgTree::recurRead(ifstream& myFile, TreeNode* parent) {
	bool valid = true;
	string line;
	getline(myFile, line);
	TreeNode* lefty = new TreeNode();
	if (line == ")") {
		return true;
	}
	if (line.find(", ") == -1) {
		return false;
	}
	else {
		
		lefty->title = line.substr(0, line.find(", "));
		lefty->name = line.substr(line.find(", ") + 2, line.size() - line.find(", ") - 2);
		parent->child = lefty;
		valid = recurRead(myFile, lefty);
	}
	for (string line; getline(myFile, line);) {
		if (line == ")") {
			return valid  && true;
		}
		if (line.find(", ") == -1) {
			return false;
		}
		else {
			TreeNode* temp = new TreeNode();
			temp->title = line.substr(0, line.find(", "));
			temp->name = line.substr(line.find(", ") + 2, line.size() - line.find(", ") - 2);
			lefty->right = temp;
			valid = recurRead(myFile, temp)&&valid;
			lefty = temp;
		}
	}

	return valid;
}

/*
	Writes a tree to a file
	Runs in O(n) time
*/
void OrgTree::write(string filename) {
	ofstream myFile(filename);
	recurwrite(myFile, root);
}
void OrgTree::recurwrite(ofstream& fileName, TreeNode* root) {
	if (root == NULL) {
		fileName << ")" << endl;
		return;
	}
	fileName << root->title << ", " << root->name << endl;
	recurwrite(fileName, root->child);

	
	if (root->right != NULL) {
		recurwrite(fileName, root->right);
	}
	else {
		if(root != this->root)
			fileName << ")" << endl;
	}
}

