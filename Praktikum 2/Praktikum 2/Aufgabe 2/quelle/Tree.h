/*************************************************
* ADS Praktikum 2.2
* Tree.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>
#include "TreeNode.h"
#include "catch.h"

using namespace std;

class Tree{
	
	private: 
		///////////////////////////////////////
		// Ihr Code hier:	
			
		TreeNode* anker = nullptr;
		int NodeIDCounter = 0;

		//
		////////////////////////////////////	
	
	public:
		///////////////////////////////////////
		// Ihr Code hier:	
		
		Tree() = default;

		void addNode(string Name, int Alter, double Einkommen, int PLZ);
		void deleteNode(int NodePosID);
		bool searchNode(string Name);
		void printAll();

		//Hilfe f�r delete
		TreeNode* minorNode(TreeNode* node, TreeNode*& parent);
		//
		////////////////////////////////////
		// friend-Funktionen sind f�r die Tests erforderlich und m�ssen unangetastet bleiben! 
		friend TreeNode * get_anker(Tree& TN);
};
