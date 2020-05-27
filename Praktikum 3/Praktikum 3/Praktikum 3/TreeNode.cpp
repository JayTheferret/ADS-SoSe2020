/*************************************************
* ADS Praktikum 2.2
* TreeNode.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>


////////////////////////////////////
// Ihr Code hier:



//
////////////////////////////////////

void TreeNode::print()
{
	cout << "NodeID: " << NodeID
		<< ", Name: " << Name
		<< ", Alter: " << Alter
		<< ", Einkommen: " << Einkommen
		<< ", PLZ: " << PLZ
		<< "; PosID: " << NodePosID
		<< endl;
}