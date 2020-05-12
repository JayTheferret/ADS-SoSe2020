#include "List.h"

List::List()
{
	// Konstruktor f�r eine leere Liste
	head_tail = new Node;
	list_size = 0;
	temp = false;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
}

List::List(const List & _List)
{
	// Konstruktor mit �bergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List.list_form;
	head_tail = new Node;
	list_size = 0;
	temp = _List.temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node * tmp_node;
	tmp_node = _List.head_tail->next;
	while (tmp_node != _List.head_tail)
	{
		head_tail->prev = new Node(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;		// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
}

List::List(const List * _List)
{
	// Konstruktor mit �bergabe einer Liste, die dann kopiert wird.
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	list_form = _List->list_form;
	head_tail = new Node;
	list_size = 0;
	temp = _List->temp;
	head_tail->next = head_tail;
	head_tail->prev = head_tail;
	Node * tmp_node;
	tmp_node = _List->head_tail->next;
	while (tmp_node != _List->head_tail)
	{
		head_tail->prev = new Node(tmp_node->key, head_tail->prev->next, head_tail->prev);
		head_tail->prev->prev->next = head_tail->prev;
		list_size++;
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;		// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
}

List::~List()
{
	// Dekonstruktor
	// Alle Knoten der Liste m�ssen gel�scht werden, wenn die Liste gel�scht wird.

	while (head_tail->next != head_tail) {

		del(head_tail->next->key);
	}

	delete head_tail;

/*
	hier alle Knoten l�schen, die im Objekt List allokiert wurden
*/
}

void List::insertFront(int key)
{
	// Einf�gen eines neuen Knotens am Anfang der Liste

	Node* new_head = new Node;
	new_head->key = key;

	head_tail->next->prev = new_head;
	new_head->next = head_tail->next;

	head_tail->next = new_head;
	new_head->prev = head_tail;

	list_size++;
/*
	Einen neuen Knoten mit dem Schl�sselwert key am Anfang der Liste einf�gen
*/
}

// getauscht mit List::insertFront(List& _List)
void List::insertBack(List & _List)
{
	// Einf�gen einer vorhandenen Liste am Anfang

	//insertFront(&_List); //spart duplikation -> �bergibt pointer auf Liste

	if (_List.head_tail->next == _List.head_tail) {  //wenn einzuf�gende Liste Leer -> nichts tun/return
		return;
	}

	head_tail->next->prev = _List.head_tail->prev;
	_List.head_tail->prev->next = head_tail->next;

	head_tail->next = _List.head_tail->next;
	_List.head_tail->next->prev = head_tail;

	_List.head_tail->prev = _List.head_tail;
	_List.head_tail->next = _List.head_tail;

	list_size += _List.list_size; //gr��e anpassen
	_List.list_size = 0; //andere Liste ist jetzt leer, Size = 0

	/*	
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden. 
	*/
/*
	Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
	Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) �bertragen ohne sie zu kopieren!
*/
}

// getauscht mit List::insertFront(List* _List)
void List::insertBack(List * _List)
{
	// Einf�gen einer vorhandenen Liste am Anfang

	if (_List->head_tail->next == _List->head_tail) {  //wenn einzuf�gende Liste Leer -> nichts tun/return
		return;
	}

	head_tail->next->prev = _List->head_tail->prev;
	_List->head_tail->prev->next = head_tail->next;

	head_tail->next = _List->head_tail->next;
	_List->head_tail->next->prev = head_tail;

	_List->head_tail->prev = _List->head_tail;
	_List->head_tail->next = _List->head_tail;

	list_size += _List->list_size; //gr��e anpassen
	_List->list_size = 0; //andere Liste ist jetzt leer, Size = 0


	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden. 	
	*/
/*
	Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
	Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) �bertragen ohne sie zu kopieren!
*/
}

void List::insertBack(int key)
{
	// Einf�gen eines neuen Knotens am Ende der Liste

	Node* new_tail = new Node;
	new_tail->key = key;

	head_tail->prev->next = new_tail;
	new_tail->prev = head_tail->prev;

	head_tail->prev = new_tail;
	new_tail->next = head_tail;

	list_size++;
/*
	Einen neuen Knoten mit dem Schl�sselwert key am Ende der Liste einf�gen
*/
}

// getauscht mit List::insertBack(List& _List)
void List::insertFront(List & _List)
{
	// Einf�gen einer vorhandenen Liste am Ende

	if (_List.head_tail->next == _List.head_tail) {  //wenn einzuf�gende Liste Leer -> nichts tun/return
		return;
	}

	head_tail->prev->next = _List.head_tail->next;
	_List.head_tail->next->prev = head_tail->prev;

	head_tail->prev = _List.head_tail->prev;
	_List.head_tail->prev->next = head_tail;

	_List.head_tail->prev = _List.head_tail;
	_List.head_tail->next = _List.head_tail;

	list_size += _List.list_size; //gr��e anpassen
	_List.list_size = 0; //andere Liste ist jetzt leer, Size = 0


	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden. 
	*/
/*
	Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
	Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
*/
}

// getauscht mit List::insertBack(List* _List)
void List::insertFront(List * _List)
{
	// Einf�gen einer vorhandenen Liste am Ende

	if (_List->head_tail->next == _List->head_tail) {  //wenn einzuf�gende Liste Leer -> nichts tun/return
		return;
	}

	head_tail->prev->next = _List->head_tail->next;
	_List->head_tail->next->prev = head_tail->prev;

	head_tail->prev = _List->head_tail->prev;
	_List->head_tail->prev->next = head_tail;

	_List->head_tail->prev = _List->head_tail;
	_List->head_tail->next = _List->head_tail;

	list_size += _List->list_size; //gr��e anpassen
	_List->list_size = 0; //andere Liste ist jetzt leer, Size = 0

	/*
	Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
	Die einzuf�gende Liste _List ist anschlie�end leer.
	Es darf keine Schleife und kein new benutzt werden. 
	*/
/*
	Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
	Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
*/
}

bool List::getFront(int & key)
{
	// entnehmen des Knotens am Anfang der Liste
	// der Wert wird als Parameter zur�ckgegeben
	// der Knoten wird entnommen

	if (head_tail->next == head_tail) { //kein wert zum entnehmen vorhanden
		return false;
	}

	Node* temp = head_tail->next;

	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;

	key = temp->key;

	delete temp;
	list_size--;

	return true;

/*
	Der Wert des vorderen Schl�sselknotens wird r�ckgegeben und der Knoten gel�scht.
	Die Methode del(key) darf nicht zum l�schen benutzt werden.
*/
	//return false;
}

bool List::getBack(int & key)
{	// entnehmen des Knotens am Ende der Liste
	// der Wert wird als Parameter zur�ckgegeben
	// der Knoten wird entnommen

	if (head_tail->next == head_tail) { //kein wert zum entnehmen vorhanden
		return false;
	}

	Node* temp = head_tail->prev;

	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;

	key = temp->key;

	delete temp;
	list_size--;

	return true;

/*
	Der Wert des letzten Schl�sselknotens wird r�ckgegeben und der Knoten gel�scht.
	Die Methode del(key) darf nicht zum l�schen benutzt werden.
*/
	//return false;
}

bool List::del(int key)
{
	// L�schen eines gegebenen Knotens

	Node* temp = head_tail->next;
	
	//suche

	while (temp->key != key && temp != head_tail) {
		temp = temp->next;
	}
	//nicht gefunden
	if(temp == head_tail){
		return false;
	}
	 
	//gefunden
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;

	delete temp;
	list_size--;

	return true;
/*
	L�schen des Knotens mit dem Schl�ssel key
*/
	//return false;
}

bool List::search(int key)
{
	// suchen eines Knotens

	Node* temp = head_tail->next;

	//suche

	while (temp->key != key && temp != head_tail) {
		temp = temp->next;
	}

	//gefunden wenn temp nicht komplett durchgelaufen is, ansonsten return false
	return temp != head_tail;
/*
	suchen ob ein Knoten mit dem Schl�ssel key existiert.
*/
	//return false;
}

bool List::swap(int key1, int key2)
{
	// Vertauschen von zwei Knoten
	// Dabei werden die Zeiger der Knoten und deren Nachbarn ver�ndert.

	// suchen eines Knotens

	Node* node1 = head_tail->next;
	Node* node2 = head_tail->next;


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

	Node* temp = new Node;

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
	Es d�rfen nicht nur einfach die Schl�ssel in den Knoten getauscht werden!
	Die Knoten sind in der Kette umzuh�ngen.
*/
	//return false;
}

int List::size(void)
{
	// R�ckgabe der Knoten in der Liste mit O(1)

	return list_size;
/*
	Anzahl der Knoten in der Liste zur�ckgeben.
*/
	//return 0;
}

bool List::test(void)
{
	// Testmethode: die Methode durchl�uft die Liste vom Anfang bis zum Ende und zur�ck
	// Es werden dabei die Anzahl der Knoten gez�hlt.
	// Stimmt die Anzahl der Knoten �berein liefert die Methode true
	Node * tmp = head_tail->next;
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

List & List::operator = (const List & _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;		//  !! keine Aktion notwendig
	list_form = _List.list_form;
	Node * tmp_node;
	if (list_size)
	{
		Node * tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this l�schen
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
	if (_List.temp) delete & _List;			// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	return *this;
}

List & List::operator = (const List * _List)
{
	// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;		//  !! keine Aktion notwendig
	list_form = _List->list_form;
	Node * tmp_node;
	if (list_size)
	{
		Node * tmp_del;
		tmp_node = head_tail->next;
		while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this l�schen
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
	if (_List->temp) delete _List;			// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	return *this;
}

List & List::operator + (const List & List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht ver�ndert. Es entsteht eine neue Ergebnisliste.
	Node * tmp_node;
	List * tmp;
	if (temp) {										// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {	
		tmp = new List(this);						// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine tempor�re Liste handelt
	}
	if (List_Append.list_size) {					// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append.head_tail->next;
		while (tmp_node != List_Append.head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht						
	return *tmp;
}

List & List::operator + (const List * List_Append)
{
	// Die Methode +
	// Es werden zwei Listen aneinander gehangen.
	// Dabei werden beide Ursprungslisten nicht ver�ndert. Es entsteht eine neue Ergebnisliste.
	Node * tmp_node;
	List * tmp;
	if (temp) {										// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {
		tmp = new List(this);						// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;							// Merker setzten, dass es sich um eine tempor�re Liste handelt
	}
	if (List_Append->list_size) {					// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append->head_tail->next;
		while (tmp_node != List_Append->head_tail) {
			tmp->insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht					
	return *tmp;
}

void List::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	// Setzen des Formates f�r die Ausgabesteuerung der Liste bei cout
	// das Format wird f�r den �berladenen Operator << verwendet
	list_form.start = start;
	list_form.zwischen = zwischen;
	list_form.ende = ende;
}

std::ostream & operator<<(std::ostream  & stream, List const & Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste.list_form.start;
	for (Node * tmp = Liste.head_tail->next; tmp != Liste.head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.head_tail ? Liste.list_form.ende : Liste.list_form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
	return stream;
}

std::ostream & operator << (std::ostream & stream, List const * Liste)
{
	// Ausgabe der Liste mit cout
	stream << Liste->list_form.start;
	for (Node * tmp = Liste->head_tail->next; tmp != Liste->head_tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->head_tail ? Liste->list_form.ende : Liste->list_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
	return stream;
}
