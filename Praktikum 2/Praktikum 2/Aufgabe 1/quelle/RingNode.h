/*************************************************
* ADS Praktikum 2.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>

using namespace std;

class RingNode {

private:
	// Ihr Code hier:
	int OldAge = 0;
	string Description;
	string SymbolicData;
	RingNode* Mnext;

public:
	// Ihr Code hier:
	RingNode();
	RingNode(int age, string desc, string data) : OldAge(age), Description(desc), SymbolicData(data), Mnext(nullptr){};

	//getter und Setter
	int			getAge() {return OldAge; };
	void		setAge(int age) { OldAge = age; };

	string		getDescription() {return Description;};
	void		setDescription(string desc) { Description = desc; };

	string		getData() { return SymbolicData; };
	void		setData(string data) { SymbolicData = data; };

	RingNode* getNext() {return Mnext;};
	void		setNext(RingNode* next) { Mnext = next; };

	//funktionen
	void print();
};
