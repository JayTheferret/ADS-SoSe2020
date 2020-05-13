/*************************************************
* ADS Praktikum 2.1
* main.cpp
*
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.hpp"


using namespace std;

Ring ring;

int main()
{
	int result = Catch::Session().run();
	// Ihr Code hier:
	bool quit = false;
	do {
	cout << "    =============================="	<< endl
		 << "   |                              |"	<< endl
		 << "   |   1) Backup einfuegen        |"	<< endl
		 << "   |   2) Backup suchen           |"	<< endl
		 << "   |   3) Alle Backups ausgeben   |"	<< endl
		 << "   |   4) Quit                    |"	<< endl
		 << "   |                              |"	<< endl
		 << "    =============================="	<< endl;

	int auswahl = 0;

	cout << "?> ";
	cin >> auswahl;
	
		if (auswahl == 1) {
			string desc;
			string data;

			cout << "Neuen Datensatz einfuegen" << endl
				<< "Beschrebung: ?";
			cin >> desc;
			cout << "Daten: ?";
			cin >> data;

			ring.addNode(data, desc);

			cout << "Datensatz hinzugefuegt." << endl;

		}

		else if (auswahl == 2) {
			string zufinden;
			bool gefunden;
			RingNode* gefundeneNode = nullptr;

			cout << "Nach welchen Daten soll gesucht werden?" << endl;
			cin >> zufinden;

			gefunden = ring.search(zufinden, gefundeneNode);

			if (gefunden) {
				cout << "Gefunden in Backup: ";
				gefundeneNode->print();
				cout << endl;
			}
			else {
				cout << "Datensatz konnte nicht gefunden werden." << endl;
			}
		}

		else if (auswahl == 3) {
			ring.print();
		}
		else if (auswahl == 4) {
			quit = true;
		}
		else {
			cout << "Ungueltige Eingabe!" << endl;
		}
	} while (!quit);

	//
	///////////////////////////////////////
	system("Pause");
	return 0;
}
