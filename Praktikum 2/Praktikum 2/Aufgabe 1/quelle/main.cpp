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


int main()
{
	int result = Catch::Session().run();
	// Ihr Code hier:

	cout << "=======================================" << endl;
	cout << "1) Backup einfuegen" << endl
		<< "2) Backup suchen" << endl
		<< "3) Alle Backups ausgeben" << endl;

	int auswahl = 0;

	cout << "?> ";
	cin >> auswahl;

	if (auswahl == 1) {
		cout << "Neuen Datensatz einfuegen" << endl;
	}

	if (auswahl == 2) {
		cout << "Nach welchen Daten soll gesucht werden?" << endl;
	}

	if (auswahl == 3) {
		cout << "ausgabe";
	}


	//
	///////////////////////////////////////
	system("Pause");
	return 0;
}
