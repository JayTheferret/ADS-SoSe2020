/*************************************************
* ADS Praktikum 2.2
* main.cpp
*
*************************************************/
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "Tree.h"
#include "catch.h"

using namespace std;

///////////////////////////////////////
// Hilfsmethoden fürs Menü hier:



//
///////////////////////////////////////
int main() {

	int result = Catch::Session().run();

	///////////////////////////////////////
	// Ihr Code hier:
	Tree My_Tree;
	bool quit = false;
	int input;
	do {
		cout << "    ====================================" << endl
			<< "   |                                     |" << endl
			<< "   |   1) Datensatz einfuegen, manuell   |" << endl
			<< "   |   2) Datensatz enfuegen, CSV Datei  |" << endl
			<< "   |   3) Datensatz löschen              |" << endl
			<< "   |   4) Suchen                         |" << endl
			<< "   |   4) Datenstruktur anzeigen         |" << endl
			<< "   |   5) Quit                           |" << endl
			<< "   |                                     |" << endl
			<< "    =====================================" << endl;

		cout << "?> ";
		cin >> input;

		if (input == 1) {

			string name;
			int alter, plz;
			double einkommen;

			cout << "Bitte geben Sie den Datensatz ein." << endl
				<< "Name: ";
			cin >> name;
			cout << "Alter: ";
			cin >> alter;
			cout << "Einkommen: ";
			cin >> einkommen;
			cout << "PLZ: ";
			cin >> plz;

			My_Tree.addNode(name, alter, einkommen, plz);

			cout << "Ihr Datensatz wurde eingefügt.";
		}

		else if (input == 2) {
			char input2;

			do { //nur richtige eingaben annehmen sonst weiter nachfragen
				cout << "Moechten Sie die Daten aus der Datei \"ExportZielanalyse.csv\" importieren? (j/N) ?> ";
				cin >> input2;
			} while (input2 != 'j' && input2 != 'n');

			if (input2 == 'j') {
				fstream daten("ExportZielanalys.csv", ios::in);

				string name = "";
				int alter = 0, plz = 0;
				double einkommen = 0.0;

				while (!daten.eof()) { //solange nicht am ende
					getline(daten, name, ';');
					
					string speicher;

					getline(daten, speicher, ';'); //alter als string einlesen
					alter = stoi(speicher); //string to integer

					getline(daten, speicher, ';');
					einkommen = stod(speicher); //string to double
					
					getline(daten, speicher, '\n');
					plz = stoi(speicher);

					My_Tree.addNode(name, alter, einkommen, plz); //in Baum einfügen

				}

				daten.close(); //Datei schließen
				cout << " Daten wurden dem Baum hinzugefuegt." << endl;
			}
			else if (input == 'n') { break; }
		}

		else if (input == 3) {

			int PosID;

			cout	<< "Bitte geben Sie den zu loeschenden Datensatz an." << endl
					<< "PosID ?> ";
			cin		>> PosID;

			My_Tree.deleteNode(PosID);

			cout << "Datensatz wurde geloescht." << endl;
		}

		else if (input == 4) {

			string name;

			cout << "Bitte geben Sie den zu suchenden Datensatz an" << endl;
			cin >> name;

			cout << "Fundstellen: " << endl;

			My_Tree.searchNode(name);
		}

		else if (input == 5) {

			My_Tree.printAll();
		}

		else if (input == 6) {
			quit = true;
}
	} while (!quit);
	

	//
	///////////////////////////////////////
	system("PAUSE");

	return 0;
}
