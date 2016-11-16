// OrganizationTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OrgTree.h"
#include <string>
#include <iostream>

using namespace std;


int main()
{
	OrgTree myCompany = OrgTree();
	myCompany.addRoot("poopyhead", "asscheeks");		// tests addRoot on empty tree;
	myCompany.addRoot("pissypants", "shclongus");		// test addRoot on tree with data;
	
	myCompany.printSubTree(myCompany.getRoot());
	
	myCompany.hire(myCompany.find("poopyhead"), "hierophant", "god emperor");
	myCompany.hire(myCompany.find("pissypants"), "hierophant", "god emperor");
	myCompany.printSubTree(myCompany.getRoot());
	myCompany.fire("poopyhead");
	
	myCompany.read("C:\\Users\\What you should use\\Desktop\\data");
	myCompany.printSubTree(myCompany.getRoot());
	std::cout << "C:\\Users\\What you should use\\Desktop\\data.txt";
	myCompany.write("C:\\Users\\What you should use\\Desktop\\data2");
	int n = 0;
    return 0;
}

