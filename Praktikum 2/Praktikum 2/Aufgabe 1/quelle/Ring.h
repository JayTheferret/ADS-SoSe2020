/*************************************************
* ADS Praktikum 2.1
* Ring.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .h
#pragma once
#include <string>
#include "catch.hpp"
#include"RingNode.h"

using namespace std;

class Ring{
	
	private:
		// Ihr Code hier:	

		int AnzahlNodes;
		RingNode* anker;
		////////////////////////////////////
	public:
		// Ihr Code hier:
		Ring() {
			anker = nullptr;
			AnzahlNodes = 0;
		};

		void addNode(string SymbolicData,string Description);
		bool search(string SymbolicData);
		bool search(string SymbolicData, RingNode*& t);
		void print();


		//
		////////////////////////////////////
		// friend Funktionen müssen unangetastet bleiben! 
		friend RingNode * get_anker(Ring& r);
		friend int get_AnzahlNodes(Ring& r);
};
