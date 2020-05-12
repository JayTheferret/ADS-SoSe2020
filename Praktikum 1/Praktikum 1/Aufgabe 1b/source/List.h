#ifndef LIST_H
#define LIST_H
#include "Node.h"
#include <string>
#include <iostream>

template <class T>
class List
{
	struct form { std::string start = "<< "; std::string zwischen = ", "; std::string ende = " >>\n"; } list_form;
	Node<T>* head_tail;
	int list_size;
	bool temp;


	//-------
public:
	List();
	List(const List& _List);
	List(const List<T>* _List);
	~List();

	void insertFront(T key);
	void insertBack(List<T>& _List);
	void insertBack(List<T>* _List);
	void insertBack(T key);
	void insertFront(List<T>& _List);
	void insertFront(List<T>* _List);
	bool getFront(T& key);
	bool getBack(T& key);
	bool del(T key);
	bool search(T key);
	bool swap(T key1, T key2);
	int  size(void);
	bool test(void);
	

	//-------
	/*
	Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
	kann ein Stapel oder Warteschlange realisiert werden.
	*/

	void format(const std::string & start, const std::string & zwischen, const std::string & ende);	
											// Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
											// start: stirng vor der Ausgabe der Liste
											// zwischen: string zwischen Listenknoten
											// ende: string am Ende der Liste
	List<T> & operator = (const List<T> & _List);						// Zuweisungsoperator definieren
	List<T> & operator = (const List<T> * _List);						// Zuweisungsoperator definieren
	List<T> & operator + (const List<T> & List_Append);					// Listen zusammenführen zu einer Liste
	List<T> & operator + (const List<T> * List_Append);					// Listen zusammenführen zu einer Liste
	template <typename T>
	friend std::ostream & operator << (std::ostream & stream, List<T> const & Liste);		// Ausgabeoperator überladen
	template <typename T>
	friend std::ostream & operator << (std::ostream & stream, List<T> const * Liste);		// Ausgabeoperator überladen
};


//einfügen

template <typename T>
List<T>::List()
{
	// Konstruktor für eine leere Liste
	head_tail = new Node<T>;
	list_size = 0;
	temp = false;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
}

template <typename T>
List<T>::List(const List<T>& _List)
{
	// Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List.list_form;
	head_tail = new Node<T>;
	list_size = 0;
	temp = _List.temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node<T>* tmp_node;
	tmp_node = _List.head_tail->next;
	while (tmp_node != _List.head_tail)
	{
		head_tail->prev = new Node<T>(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete& _List;		// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
}

template <typename T>
List<T>::List(const List<T>* _List)
{
	// Konstruktor mit Übergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List->list_form;
	head_tail = new Node<T>;
	list_size = 0;
	temp = _List->temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node<T>* tmp_node;
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)
	{
		head_tail->prev = new Node<T>(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;		// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
}

template <typename T>
List<T>::~List()
{
	// Dekonstruktor
	// Alle Knoten der Liste müssen gelöscht werden, wenn die Liste gelöscht wird.

	while (head_tail->next != head_tail) {

		del(head_tail->next->key);
	}

	delete head_tail;

	/*
		hier alle Knoten löschen, die im Objekt List allokiert wurden
	*/
}

template <typename T>
void List<T>::insertFront(T key)
{
	// Einfügen eines neuen Knotens am Anfang der Liste

	Node<T>* new_head = new Node<T>;
	new_head->key = key;

	head_tail->next->prev = new_head;
	new_head->next = head_tail->next;

	head_tail->next = new_head;
	new_head->prev = head_tail;

	list_size++;
	/*
		Einen neuen Knoten mit dem Schlüsselwert key am Anfang der Liste einfügen
	*/
}

// getauscht mit List<T>::insertFront(List& _List)
template <typename T>
void List<T>::insertBack(List<T>& _List)
{
	// Einfügen einer vorhandenen Liste am Anfang

	//insertFront(&_List); //spart duplikation -> übergibt pointer auf Liste

	if (_List.head_tail->next == _List.head_tail) {  //wenn einzufügende Liste Leer -> nichts tun/return
		return;
	}

	head_tail->next->prev = _List.head_tail->prev;
	_List.head_tail->prev->next = head_tail->next;

	head_tail->next = _List.head_tail->next;
	_List.head_tail->next->prev = head_tail;

	_List.head_tail->prev = _List.head_tail;
	_List.head_tail->next = _List.head_tail;

	list_size += _List.list_size; //größe anpassen
	_List.list_size = 0; //andere Liste ist jetzt leer, Size = 0

	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
		Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
	*/
}

// getauscht mit List<T>::insertFront(List* _List)
template <typename T>
void List<T>::insertBack(List<T>* _List)
{
	// Einfügen einer vorhandenen Liste am Anfang

	if (_List->head_tail->next == _List->head_tail) {  //wenn einzufügende Liste Leer -> nichts tun/return
		return;
	}

	head_tail->next->prev = _List->head_tail->prev;
	_List->head_tail->prev->next = head_tail->next;

	head_tail->next = _List->head_tail->next;
	_List->head_tail->next->prev = head_tail;

	_List->head_tail->prev = _List->head_tail;
	_List->head_tail->next = _List->head_tail;

	list_size += _List->list_size; //größe anpassen
	_List->list_size = 0; //andere Liste ist jetzt leer, Size = 0


	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
		Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) übertragen ohne sie zu kopieren!
	*/
}

template <typename T>
void List<T>::insertBack(T key)
{
	// Einfügen eines neuen Knotens am Ende der Liste

	Node<T>* new_tail = new Node<T>;
	new_tail->key = key;

	head_tail->prev->next = new_tail;
	new_tail->prev = head_tail->prev;

	head_tail->prev = new_tail;
	new_tail->next = head_tail;

	list_size++;
	/*
		Einen neuen Knoten mit dem Schlüsselwert key am Ende der Liste einfügen
	*/
}

// getauscht mit List<T>::insertBack(List& _List)
template <typename T>
void List<T>::insertFront(List<T>& _List)
{
	// Einfügen einer vorhandenen Liste am Ende

	if (_List.head_tail->next == _List.head_tail) {  //wenn einzufügende Liste Leer -> nichts tun/return
		return;
	}

	head_tail->prev->next = _List.head_tail->next;
	_List.head_tail->next->prev = head_tail->prev;

	head_tail->prev = _List.head_tail->prev;
	_List.head_tail->prev->next = head_tail;

	_List.head_tail->prev = _List.head_tail;
	_List.head_tail->next = _List.head_tail;

	list_size += _List.list_size; //größe anpassen
	_List.list_size = 0; //andere Liste ist jetzt leer, Size = 0


	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
		Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
	*/
}

// getauscht mit List<T>::insertBack(List* _List)
template <typename T>
void List<T>::insertFront(List<T>* _List)
{
	// Einfügen einer vorhandenen Liste am Ende

	if (_List->head_tail->next == _List->head_tail) {  //wenn einzufügende Liste Leer -> nichts tun/return
		return;
	}

	head_tail->prev->next = _List->head_tail->next;
	_List->head_tail->next->prev = head_tail->prev;

	head_tail->prev = _List->head_tail->prev;
	_List->head_tail->prev->next = head_tail;

	_List->head_tail->prev = _List->head_tail;
	_List->head_tail->next = _List->head_tail;

	list_size += _List->list_size; //größe anpassen
	_List->list_size = 0; //andere Liste ist jetzt leer, Size = 0

	/*
	Die einzufügenden Knoten werden übernommen (nicht kopiert)
	Die einzufügende Liste _List ist anschließend leer.
	Es darf keine Schleife und kein new benutzt werden.
	*/
	/*
		Es wird ein Objekt übergeben in dem Knoten vorhanden sein können.
		Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
	*/
}

template <typename T>
bool List<T>::getFront(T& key)
{
	// entnehmen des Knotens am Anfang der Liste
	// der Wert wird als Parameter zurückgegeben
	// der Knoten wird entnommen

	if (head_tail->next == head_tail) { //kein wert zum entnehmen vorhanden
		return false;
	}

	Node<T>* temp = head_tail->next;

	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;

	key = temp->key;

	delete temp;
	list_size--;

	return true;

	/*
		Der Wert des vorderen Schlüsselknotens wird rückgegeben und der Knoten gelöscht.
		Die Methode del(key) darf nicht zum löschen benutzt werden.
	*/
	//return false;
}

template <typename T>
bool List<T>::getBack(T& key)
{	// entnehmen des Knotens am Ende der Liste
	// der Wert wird als Parameter zurückgegeben
	// der Knoten wird entnommen

	if (head_tail->next == head_tail) { //kein wert zum entnehmen vorhanden
		return false;
	}

	Node<T>* temp = head_tail->prev;

	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;

	key = temp->key;

	delete temp;
	list_size--;

	return true;

	/*
		Der Wert des letzten Schlüsselknotens wird rückgegeben und der Knoten gelöscht.
		Die Methode del(key) darf nicht zum löschen benutzt werden.
	*/
	//return false;
}

template <typename T>
bool List<T>::del(T key)
{
	// Löschen eines gegebenen Knotens

	Node<T>* temp = head_tail->next;

	//suche

	while (temp->key != key && temp != head_tail) {
		temp = temp->next;
	}
	//nicht gefunden
	if (temp == head_tail) {
		return false;
	}

	//gefunden
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;

	delete temp;
	list_size--;

	return true;
	/*
		Löschen des Knotens mit dem Schlüssel key
	*/
	//return false;
}

template <typename T>
bool List<T>::search(T key)
{
	// suchen eines Knotens

	Node<T>* temp = head_tail->next;

	//suche

	while (temp->key != key && temp != head_tail) {
		temp = temp->next;
	}

	//gefunden wenn temp nicht komplett durchgelaufen is, ansonsten return false
	return temp != head_tail;
	/*
		suchen ob ein Knoten mit dem Schlüssel key existiert.
	*/
	//return false;
}

template <typename T>
bool List<T>::swap(T key1, T key2)
{
	// Vertauschen von zwei Knoten
	// Dabei werden die Zeiger der Knoten und deren Nachbarn verändert.

	// suchen eines Knotens

	Node<T>* node1 = head_tail->next;
	Node<T>* node2 = head_tail->next;


	//suche key1
	while (node1->key != key1 && node1 != head_tail) {
		node1 = node1->next;
	}
	//suche key 2
	while (node2->key != key2 && node2 != head_tail) {
		node2 = node2->next;
	}

	if (node1 == head_tail || node2 == head_tail) { //einen oder beide nicht gefunden also nicht austauschen
		return false;
	}

	Node<T>* temp = new Node<T>;

	temp->next = node1->next;
	temp->prev = node1->prev;
	temp->prev->next = temp;
	temp->next->prev = temp;

	node1->next = node2->next;
	node1->prev = node2->prev;
	node1->prev->next = node1;
	node1->next->prev = node1;

	node2->next = temp->next;
	node2->prev = temp->prev;
	node2->prev->next = node2;
	node2->next->prev = node2;

	delete temp;

	return true;

	/*
		Vertauschen von zwei Knoten mit dem key1 und dem key2
		Es dürfen nicht nur einfach die Schlüssel in den Knoten getauscht werden!
		Die Knoten sind in der Kette umzuhängen.
	*/
	//return false;
}

template <typename T>
int List<T>::size(void)
{
	// Rückgabe der Knoten in der Liste mit O(1)

	return list_size;
	/*
		Anzahl der Knoten in der Liste zurückgeben.
	*/
	//return 0;
}

template <typename T>
bool List<T>::test(void)
{
	// Testmethode: die Methode durchläuft die Liste vom Anfang bis zum Ende und zurück
	// Es werden dabei die Anzahl der Knoten gezählt.
	// Stimmt die Anzahl der Knoten überein liefert die Methode true
	Node<T>* tmp = head_tail->next;
	int i_next = 0, i_prev = 0;
	while (tmp != head_tail) {
		tmp = tmp->next;
		if (i_next > list_size) return false;
		i_next++;
	}
	if (i_next != list_size) return false;
	tmp = head_tail->prev;
	while (tmp != head_tail) {
		tmp = tmp->prev;
		if (i_prev > list_size) return false;
		i_prev++;
	}
	return i_prev == i_next;
}


//einfügen


template <class T>
List<T> & List<T>::operator = (const List<T> & _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;		//  !! keine Aktion notwendig
	list_form = _List.list_form;
	Node<T> * tmp_node;
	if (list_size)
	{
		Node<T> * tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List.head_tail->next;		// Die Listen-Knotenwerte werden kopiert
	while (tmp_node != _List.head_tail)
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;			// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
	return *this;
}

template <class T>
List<T> & List<T>::operator = (const List<T> * _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;		//  !! keine Aktion notwendig
	list_form = _List->list_form;
	Node<T> * tmp_node;
	if (list_size)
	{
		Node * tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		list_size = 0;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)	// Die Listen-Knotenwerte werden kopiert
	{
		insertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;			// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
	return *this;
}

template <class T>
List<T> & List<T>::operator + (const List<T> & List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue Ergebnisliste.
	Node<T> * tmp_node;
	List * tmp;
	if (temp) {										// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp = new List<T>(this);					// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine temporäre Liste handelt
	}
	if (List_Append.list_size) {					// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append.head_tail->next;
		while (tmp_node != List_Append.head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht						
	return *tmp;
}

template <class T>
List<T> & List<T>::operator + (const List<T> * List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht verändert. Es entsteht eine neue Ergebnisliste.
	Node<T> * tmp_node;
	List<T> * tmp;
	if (temp) {										// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp = new List<T>(this);					// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine temporäre Liste handelt
	}
	if (List_Append->list_size) {					// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append->head_tail->next;
		while (tmp_node != List_Append->head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht					
	return *tmp;
}

template <class T>
void List<T>::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	// Setzen des Formates für die Ausgabesteuerung der Liste bei cout
	// das Format wird für den überladenen Operator << verwendet
	list_form.start = start;
	list_form.zwischen = zwischen;
	list_form.ende = ende;
}

template <class T>
std::ostream & operator<<(std::ostream  & stream, List<T> const & Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste.list_form.start;
	for (Node<T> * tmp = Liste.head_tail->next; tmp != Liste.head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.head_tail ? Liste.list_form.ende : Liste.list_form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}

template <class T>
std::ostream & operator << (std::ostream & stream, List<T> const * Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste->list_form.start;
	for (Node<T> * tmp = Liste->head_tail->next; tmp != Liste->head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->head_tail ? Liste->list_form.ende : Liste->list_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}

#endif

