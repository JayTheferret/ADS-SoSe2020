#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size) : size(size), collisionCount(0), elements(0), hashTable (new vector<int>(size, -1)) {//initialisiert mit size, übergibt wert -1
	
}

HashTable::~HashTable(){
	delete hashTable;
}

int HashTable::hashValue(int item) {
	
	int hash = item % getSize();
	int i = 0;
	int index = hash;

	while ((*hashTable)[index] != -1) { //wenn an Stelle bereits Element vorhanden
		collisionCount++;
		i++;
		index = (hash + i * i) % getSize();
	}
	return index;
}

int HashTable::insert(int item) {
	
	int index = hashValue(item);
	(*hashTable)[index] = item;

	elements++;

	return item; 
}


int HashTable::at(int i) {
	return hashTable->at(i);
}

int HashTable::getCollisionCount() {
	return this->collisionCount;
}

int HashTable::getSize() {
	return this->size;
}

int HashTable::getElements() {
	return this->elements;
}
