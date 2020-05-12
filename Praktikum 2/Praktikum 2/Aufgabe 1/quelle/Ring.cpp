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
	RingNode* newNode = new RingNode(0, Description, SymbolicData);
	
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
	/*else if (AnzahlNodes == 6) {
		//max Anzahl -> ältestens ersetzen
		RingNode* cur = anker->getNext(); //current eins weiter als Anker
		while (cur != anker) { //durchlaufen
			cur->setAge(cur->getAge() +1); //alter höher
			cur = cur->getNext(); //weiterlaufen
		}

		RingNode* temp = anker->getNext(); //temp erstellen auf nächsten von anker
		cur->setNext(temp->getNext()); //cur mit eins weiter als temp
		anker->setNext(cur);
		delete temp;
		anker = cur;
	
	}*/
	//else if (AnzahlNodes) {}
}

bool Ring::search(string)
{
	return false;
}

void Ring::print()
{
}
