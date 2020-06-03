#pragma once
/*************************************************
* ADS Praktikum 2.2
* TreeNode.h
* Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
*************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode {

private:
	///////////////////////////////////////
	// Ihr Code hier:	
	int NodePosID, NodeID;
	string Name;
	int Alter, PLZ;
	double Einkommen;

	TreeNode* left = nullptr;
	TreeNode* right = nullptr;

	bool red = true;

	//
	////////////////////////////////////

public:
	///////////////////////////////////////
	// Ihr Code hier:

	TreeNode(int NodePosID, int NodeID, string Name, int Alter, double Einkommen, int PLZ) :
		NodePosID{ Alter + PLZ + int(Einkommen) },
		NodeID{ NodeID }, Name{ Name }, Alter{ Alter }, Einkommen{ Einkommen }, PLZ{ PLZ } {};



	//getter setter

	int			getNodePosID() const { return NodePosID; };
	int			getNodeID() const { return NodeID; };

	string		getName() const { return Name; };
	void		setName(string _name) { Name = _name; };

	int			getAlter() const { return Alter; };
	void		setAlter(int _alter) { Alter = _alter; };

	double		getEinkommen() const { return Einkommen; };
	void		setEinkommen(double _einkommen) { Einkommen = _einkommen; };

	int			getPLZ() const { return PLZ; };
	void		setPLZ(int _plz) { PLZ = _plz; };


	TreeNode*	getLeft()const { return left; };
	void		setLeft(TreeNode* _left) { left = _left; };

	TreeNode*	getRight() const { return right; };
	void		setRight(TreeNode* _right) { right = _right; };

	bool		getRed() {return red;};
	void		setRed(bool _red) { red = _red; };

	void print();


	//
	////////////////////////////////////
};