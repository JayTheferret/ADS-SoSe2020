#pragma once
/*************************************************
* ADS Praktikum 2.2
* Tree.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>
#include "TreeNode.h"
#include "catch.h"
#include <queue>
#include <stack>


using namespace std;

class Tree {

private:
	///////////////////////////////////////
	// Ihr Code hier:	

	TreeNode* anker = nullptr;
	int NodeIDCounter = 1;

	bool split4Node(TreeNode* node);
	bool rotateTreeRight(TreeNode* pp, TreeNode* p2);
	bool rotateTreeLeft(TreeNode* pp, TreeNode* p2);

	//
	////////////////////////////////////	

public:
	///////////////////////////////////////
	// Ihr Code hier:	

	Tree() = default;

	void printLevelOrder();

	bool addNode(string Name, int Alter, double Einkommen, int PLZ);
	void rotate(stack<TreeNode*>& path);
	void deleteNode(int NodePosID);
	bool searchNode(string Name);
	void printAll();

	//Hilfe für delete
	TreeNode* minorNode(TreeNode* node, TreeNode*& parent);

	//
	////////////////////////////////////
	// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet bleiben! 
	friend TreeNode* get_anker(Tree& TN);
};