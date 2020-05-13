/*************************************************
* ADS Praktikum 2.2
* Tree.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>

using namespace std;

////////////////////////////////////
// Ihr Code hier:

void Tree::addNode(string Name, int Alter, double Einkommen, int PLZ)
{
	TreeNode* newNode = new TreeNode{ 000, NodeIdCounter++, Name, Alter, Einkommen, PLZ };
	TreeNode* ptr = anker;
	TreeNode* tmp = nullptr;

}

void Tree::deleteNode(int NodePosID)
{
	if (!anker) { return; } //Baum leer
}

bool Tree::searchNode(string Name)
{
	return false;
}

void Tree::printAll()
{
	if (!anker) { return; } //wenn Baum leer, keine Ausgabe
	else {
		cout << "";
	}
}
