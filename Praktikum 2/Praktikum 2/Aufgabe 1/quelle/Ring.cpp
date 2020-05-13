/*************************************************
* ADS Praktikum 2.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .cpp
#include "Ring.h"
#include <iostream>

using namespace std;

// Ihr Code hier:

void Ring::addNode(string SymbolicData, string Description)
{
	RingNode* newNode = new RingNode(0, SymbolicData, Description);
	
	if (AnzahlNodes == 0) { //keine Nodes Vorhanden
		
		anker = newNode;
		newNode->setNext(anker);
		anker->setNext(newNode);
		AnzahlNodes++;
	}
	else if (AnzahlNodes != 6) {
		//dynamisch wachsen lassen

		if (AnzahlNodes == 1) { //nur ein Node vorhanden
			anker->setAge(anker->getAge() +1); //Anker eins "älter"
		}

		else {
			RingNode* cur = anker->getNext(); // zeigt auf Nachfolger von Anker

			while (cur != anker) { //durchlaufen
				cur->setAge(cur->getAge() +1); //alter höher
				cur = cur->getNext(); //weiterlaufen
			}
		}

		newNode->setNext(anker->getNext());
		anker->setNext(newNode);
		anker = (newNode);
		AnzahlNodes++;
	}

	else if (AnzahlNodes == 6) { //max Anzahl -> ältestens ersetzen
		
		RingNode* cur = anker->getNext(); //current eins weiter als Anker
		while (cur != anker) { //durchlaufen
			cur->setAge(cur->getAge() +1); //alter höher
			cur = cur->getNext(); //weiterlaufen
		}

		RingNode* temp = anker->getNext(); //temp erstellen auf nächsten von anker
		newNode->setNext(temp->getNext()); //cur mit eins weiter als temp
		anker->setNext(newNode);
		delete temp;
		anker = newNode;
	
	}
}


bool Ring::search(string SymbolicData)
{
	RingNode* temp = anker; //temporaerer Zeiger auf anker 


	//durchlaufen

	while (temp->getData() != SymbolicData && temp->getNext() != anker) {
		temp = temp->getNext();
	}
	
	if (temp->getData() == SymbolicData) { //gefunden
		return true;
	}
	//nicht gefunden
	return false;
}

bool Ring::search(string SymbolicData, RingNode*& t)
{
	RingNode* temp = anker; //temporaerer Zeiger auf anker 

	//durchlaufen

	while (temp->getData() != SymbolicData && temp->getNext() != anker) {
		temp = temp->getNext();
	}

	if (temp->getData() == SymbolicData) { //gefunden
		t = temp;
		return true;
	}
	//nicht gefunden
	return false;
}

void Ring::print()
{
	RingNode* temp = anker;

	for (int i = 0; i < AnzahlNodes; i++) {
		cout	<< "OldAge "	<< temp->getAge() 
				<< ", Descr: "	<< temp->getDescription() 
				<< ", Data: "	<< temp->getData() 
				<< endl;
		temp = temp->getNext(); // einen weiter
	}
}
