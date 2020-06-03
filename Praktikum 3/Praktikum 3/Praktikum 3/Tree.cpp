#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>

using namespace std;

bool Tree::split4Node(TreeNode* node) //Eingabeparameter = schwarzer Knoten
{
    if (anker == nullptr) return true;

    //existieren Kinder?
    else if (node->getLeft() == nullptr || node->getRight() == nullptr) return true; 
 
    //4er Knoten = Knoten mit zwei roten als Nachfolger
    else if (node->getLeft()->getRed() == true && node->getRight()->getRed() == true) {

        //umfärben
        node->setRed(true);
        node->getRight()->setRed(false);
        node->getLeft()->setRed(false);
    }

    return true;
    //frei beteiligte knoten umgefärbt, schwarz= rot und rot = schwarz
}

bool Tree::rotateTreeRight(TreeNode* pp, TreeNode* p2)
{
 
    pp->setLeft(p2->getRight());
    p2->setRight(pp);

    cout << "RR(" << p2->getNodePosID() << "," << pp->getNodePosID() << ")." << endl;

    return true;
}

bool Tree::rotateTreeLeft(TreeNode* pp, TreeNode* p2)
{
    pp->setRight(p2->getLeft());
    p2->setLeft(pp);

    cout << "LR(" << p2->getNodePosID()<< "," << pp->getNodePosID() << ")." << endl;

    return true;
}

void Tree::printLevelOrder()
{
    //Leerer Baum

    if (anker == nullptr) {
        cout << "Leerer Baum." << endl;
        return;
    }  

    //B-Baum
    cout << endl;
    cout << "Ausgabe in Levelorder als binaerer Suchbaum: " << endl
         << endl;
    cout << "ID  | Name      | Alter | Einkommen  | PLZ  | Pos" << endl;
    cout << "----+-----------+-------+------------+------+-------" << endl;

    //wie bei print all nur queue? (FIFO statt LIFO?)
    queue<TreeNode*> queue;
    queue.push(anker);

    while (!queue.empty()) //solange nicht leer 
    {         
        TreeNode* node = queue.front();
        queue.pop();

        if (node->getLeft() != nullptr) {
            queue.push(node->getLeft());
        }

        if (node->getRight() != nullptr) {
            queue.push(node->getRight());
        }
       
        cout << setw(3)  << left  << node->getNodeID() << "|"
             << setw(12) << left  << node->getName() << "|"
             << setw(7)  << right << node->getAlter() << "|"
             << setw(11) << right << node->getEinkommen() << "|"
             << setw(7)  << right << node->getPLZ() << "|"
             << setw(7)  << left  << node->getNodePosID()
             << endl;
    }


    //2-3-4 Baum (NodePosID)
    std::queue<TreeNode*> b_node;
    
    queue.push(anker);
    b_node.push(anker);

    while (!queue.empty()) //solange nicht leer 
    {
        TreeNode* node = queue.front();
        queue.pop();

        if (node->getLeft() != nullptr) {
            if (node->getLeft()->getRed() == true) { //Links = rot
                if (node->getLeft()->getLeft() != nullptr) { //muss schwarz sein
                    queue.push(node->getLeft()->getLeft());
                    b_node.push(node->getLeft()->getLeft());
                }
                if (node->getLeft()->getRight() != nullptr) { //muss schwarz sein
                    queue.push(node->getLeft()->getRight());
                    b_node.push(node->getLeft()->getRight());
                }
            }
            else { //Links = schwarz
                queue.push(node->getLeft());
                b_node.push(node->getLeft());
            }
        }

        if (node->getRight() != nullptr) {
            if (node->getRight()->getRed() == true) { //Rechts = rot
                if (node->getRight()->getLeft() != nullptr) { //muss schwarz sein
                    queue.push(node->getRight()->getLeft());
                    b_node.push(node->getRight()->getLeft());
                }
                if (node->getRight()->getRight() != nullptr) { //muss schwarz sein
                    queue.push(node->getRight()->getRight());
                    b_node.push(node->getRight()->getRight());
                }
            }
            else { //Links = schwarz
                queue.push(node->getRight());
                b_node.push(node->getRight());
            }
        }

       
    }

    //test ob schwarze Knoten richtig eingefügt
      /*while (!b_node.empty())
    {
        cout << b_node.front()->getNodePosID() << "----";
        b_node.pop();
    }*/

   
    int niv_prev = -1; //vorheriges Niveau (start bei Niveau 0 also vorher -1

    while (!b_node.empty()) { //solange noch schwarze Knoten vorhanden suchen und Niv erhoehens

        //Knoten suchen und bei schwarz auf weg niv erhöhen
        int niv = 0;
        TreeNode* cur = anker;

        if (cur == nullptr) {
            cout << "Fehler der nich kommen darf!!" << endl;
            break;
        }

        if (b_node.front() == nullptr) {
             cout << "Fehler der nich kommen darf!!" << endl;
            break;
        }

        while (cur->getNodePosID() != b_node.front()->getNodePosID()) {
            
            if (cur == nullptr) {
                cout << "Fehler der nich kommen darf!!" << endl;
                break;
            }

            if (cur->getRed() == false) { //für schwarze auf weg niv erhöhen
                niv++; 
            } 

            if (cur->getNodePosID() > b_node.front()->getNodePosID()){//kleiner->LTB

                cur = cur->getLeft(); //links weiter suchen
            }
            else {//groesser -> RTB

                cur = cur->getRight(); //rechts weiter suchen
            }
        }


        //niveau wie vorher:
        if (niv_prev == niv){
            cout << "(";

            if (b_node.front()->getLeft() != nullptr && b_node.front()->getLeft()->getRed() == true) {
                cout << b_node.front()->getLeft()->getNodePosID() << ",";
            }

            cout << b_node.front()->getNodePosID();

            if (b_node.front()->getRight() != nullptr && b_node.front()->getRight()->getRed() == true) {
                cout << "," << b_node.front()->getRight()->getNodePosID();
            }

            cout << ")";
        }

        //niveau hat sich geändert:
        else{
            cout << endl << "Niv. " << niv << ":" << "(";

            if (b_node.front()->getLeft() != nullptr && b_node.front()->getLeft()->getRed() == true) {
                cout << b_node.front()->getLeft()->getNodePosID() << ",";
            }

            cout << b_node.front()->getNodePosID();

            if (b_node.front()->getRight() != nullptr && b_node.front()->getRight()->getRed() == true) {
                cout << "," << b_node.front()->getRight()->getNodePosID();
            }

            cout << ")";
        }
       
        b_node.pop();
        niv_prev = niv;
    }

    cout << endl;
}

bool Tree::addNode(string Name, int Alter, double Einkommen, int PLZ)
{
    //nodePos berechnung
    int nodePos = Alter + PLZ + (int)Einkommen;

    TreeNode* newNode = new TreeNode(0, NodeIDCounter, Name, Alter, Einkommen, PLZ);


    if (anker == nullptr) // wenn Baum leer ist -> wie vorher im anker einfuegen
    {
        anker = newNode;
        //newNode->setRed(false); //wurzel nie rot
    }

    else {
        stack<TreeNode*> stack;  //merken in datenstruktur bsp vector <TreeNode*>

        stack.push(anker);

        split4Node(anker); //anker 4Node?

           //Baum traversieren von Wurzel bis Blatt entspr. wert

        while (stack.top() != newNode) { //solange nicht eingefügt
            split4Node(stack.top());   //if 4er -> split 4node

            if (nodePos < stack.top()->getNodePosID()) {//kleiner->LTB

                if (stack.top()->getLeft() == nullptr) {//unten angekommen
                    stack.top()->setLeft(newNode); //unten anfügen
                }

                stack.push(stack.top()->getLeft()); //links weiter suchen
            }
            else if (nodePos > stack.top()->getNodePosID()) { //groeßer -> RTB

                if (stack.top()->getRight() == nullptr) {
                    stack.top()->setRight(newNode);
                }

                stack.push(stack.top()->getRight());
            }
        }

        //bottom up untersuchen ob zwei rote aufeinander folgen, wenn ja rotation
        while (!stack.empty()) {
            rotate(stack);
            stack.pop(); //pberstes runter-> nächste drei prüfen
        }
    }
    
    //neue Node = rot (Konstruktor)
    anker->setRed(false);

    NodeIDCounter++; //hochzaehlen
    return true;
};

void Tree::rotate(stack<TreeNode*>& path) //Hilfsfunktion Praktikum 3, Rotationen und umfärben für Regeleinhaltung
{
    if (path.top() == anker) return;  
    //wird vorausgesetzt, das drei knoten  da sind. 
    if (path.size() < 3) return;

    //prüfen ob Kinder vorhanden
    //else if (path.top()->getLeft() == nullptr) return;
    //else if (path.top()->getRight() == nullptr) return;           

    TreeNode* c2 = path.top();
    path.pop();

    TreeNode* c1 = path.top();
    path.pop();

    TreeNode* p = path.top();
    path.pop();


    if (c2->getRed() && c1->getRed())
    {
        // Zwei rote Knoten

        bool left_p = p->getLeft() == c1;
        bool left_c1 = c1->getLeft() == c2;

        // Links-Links eingefügt => R-Rotation
        if (left_p && left_c1){                                                              
            rotateTreeRight(p, c1);
            c1->setRed(false);
            p->setRed(true);
            c2->setRed(true);

            if (p == anker) anker = c1;
            else if (path.top()->getLeft() == p) path.top()->setLeft(c1);
            else path.top()->setRight(c1);

            path.push(c1);
            path.push(c2);
        }

        // Rechts-Rechts eingefügt => L-Rotation
        else if (!left_p && !left_c1){
            rotateTreeLeft(p, c1);
            c1->setRed(false);
            p->setRed(true);
            c2->setRed(true);

            if (p == anker) anker = c1;
            else if (path.top()->getLeft() == p) path.top()->setLeft(c1);
            else path.top()->setRight(c1);

            path.push(c1);
            path.push(c2);
        }

        // Links-Rechts eingefügt => LR-Rotation
        else if (left_p && !left_c1){  
            rotateTreeLeft(c1, c2);
            rotateTreeRight(p, c2);
            c2->setRed(false);
            p->setRed(true);
            c1->setRed(true);

            if (p == anker) anker = c2;
            else if (path.top()->getLeft() == p) path.top()->setLeft(c2);
            else path.top()->setRight(c2);

            path.push(c2);
        }

        // Rechts-Links eingefügt => RL-Rotation
        else{
            rotateTreeRight(c1, c2);
            rotateTreeLeft(p, c2);
            c2->setRed(false);
            p->setRed(true);
            c1->setRed(true);

            if (p == anker) anker = c2;
            else if (path.top()->getLeft() == p) path.top()->setLeft(c2);
            else path.top()->setRight(c2);

            path.push(c2);
        }
    }
    else {
        path.push(p);
        path.push(c1);
        path.push(c2);
    }
};

void Tree::deleteNode(int NodePosID) {


    TreeNode* parent = nullptr;
    TreeNode* node = anker;

    while (node != nullptr && node->getNodePosID() != NodePosID) //solange nicht komplett durch und node nicht gefunden wird:
    {
        if (NodePosID < node->getNodePosID()) //weiter suchen links
        {
            parent = node;
            node = node->getLeft();
        }
        else { //weiter suchen rechts
            parent = node;
            node = node->getRight();
        }
    }

    if (node == nullptr) return; //nicht gefunden

    if (node->getLeft() != nullptr && node->getRight() != nullptr) // zwei Nachfolger vorhanden
    {
        TreeNode* minorN_parent = node;
        TreeNode* minorN = minorNode(node->getRight(), minorN_parent);  //kleinsterNode Zeiger

        //Knoten mit minorN ersetzen
        //kinder zeiger
        minorN->setLeft(node->getLeft());
        minorN_parent->setLeft(minorN->getRight());
        if (minorN_parent != node) {
            minorN->setRight(node->getRight());
        }

        if (node == anker) anker = minorN;
        else {

            // Elternknoten
            if (parent->getLeft() == node) parent->setLeft(minorN);
            else parent->setRight(minorN);
        }

    }
    else //0 oder 1 Nachfolger
    {
        TreeNode* nachfolger = nullptr;

        //Kindknoten in nachfolger -> sonst bleibt nullptr
        if (node->getLeft() != nullptr) {
            nachfolger = node->getLeft();
        }
        else if (node->getRight() != nullptr) {
            nachfolger = node->getRight();
        }

        if (node != anker)
        {
            if (parent->getLeft() == node) {
                parent->setLeft(nachfolger);
            }
            else {
                parent->setRight(nachfolger);
            }
        }
        else
        {
            anker = nachfolger;
        }
    }

    delete node;
};

TreeNode* Tree::minorNode(TreeNode* node, TreeNode*& parent)
{
    if (node == nullptr) return nullptr;

    while (node->getLeft() != nullptr)
    {
        parent = node;
        node = node->getLeft();
    }

    return node;
}

bool Tree::searchNode(std::string Name) {

    if (anker == nullptr) //baum leer -> knoten nicht vorhanden = false
        return false;

    else {

        TreeNode* cur = anker;

        stack<TreeNode*> nodeStack;
        nodeStack.push(anker);

        bool gefunden = false;

        while (!nodeStack.empty()) { //solange nicht durch

            cur = nodeStack.top(); // letzte Element in stack
            if (cur->getName() == Name) {
                cur->print();
                gefunden = true;
            }

            nodeStack.pop();

            if (cur->getLeft())
                nodeStack.push(cur->getLeft());

            if (cur->getRight())
                nodeStack.push(cur->getRight());
        }
        //wenn durchgelaufen ohne gefunden gefunden auf false->
        return gefunden;
    }
}

void Tree::printAll()                                                           //stack benutzen damit R�ckgabewert void ist.
{

    if (anker == nullptr) //Baum leer
    {
        cout << "Binaerbaum ist Leer." << endl;
        return;
    }

    else {
        cout << "ID  | Name      | Alter | Einkommen  | PLZ  | Pos" << endl;
        cout << "----+-----------+-------+------------+------+-------" << endl;

        stack<TreeNode*> stack;
        stack.push(anker); //anker geben
        while (!stack.empty()) //solange nicht leer
        {
            TreeNode* node = stack.top();
            stack.pop(); //oberstes raus

            if (node->getRight() != nullptr) {
                stack.push(node->getRight()); //rechts
            }
            if (node->getLeft() != nullptr) { //links
                stack.push(node->getLeft());
            }

            cout    << setw(3)  << left << node->getNodeID() << "|"
                    << setw(12) << left << node->getName() << "|"
                    << setw(7)  << right << node->getAlter() << "|"
                    << setw(11) << right << node->getEinkommen() << "|"
                    << setw(7)  << right << node->getPLZ() << "|"
                    << setw(7)  << left << node->getNodePosID()
                    << endl;
        }
    }
};

