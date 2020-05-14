/*************************************************
* ADS Praktikum 2.2
* Tree.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
#include <stack>

using namespace std;

////////////////////////////////////
// Ihr Code hier:

void Tree::addNode(string Name, int Alter, double Einkommen, int PLZ)
{
    //nodePos berechnung
    int nodePos = Alter + PLZ + (int)Einkommen;


    TreeNode* newNode = new TreeNode(0, NodeIDCounter, Name, Alter, Einkommen, PLZ);

    if (anker == nullptr) // wenn Baum leer ist
    {
        anker = newNode;
    }

    else //Baum nicht leer
    {
        TreeNode* cur = anker; //zeiger erstellen für Durchlauf

        while (cur != newNode) //solange nicht eingefügt
        {
            if (nodePos < cur->getNodePosID()) //kleiner -> LTB
            {
                if (cur->getLeft() == nullptr) //unterstes Blatt -> einfügen
                {
                    cur->setLeft(newNode);
                }

                cur = cur->getLeft(); //weiter gehen

            }
            else if (nodePos > cur->getNodePosID()) //größer -> RTB
            {
                // Rechter Teilbaum
                if (cur->getRight() == nullptr) //unterstes Blatt -> einfügen
                {
                    cur->setRight(newNode);
                }

                cur = cur->getRight(); //weiter gehen

            }
        }
    }

    NodeIDCounter++; //counter erhöhen
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
        else if (node->getRight() != nullptr){
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

void Tree::printAll()                                                           //stack benutzen damit Rückgabewert void ist.
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
        stack.push(anker);
        while (!stack.empty()) //solange nicht leer
        {
            TreeNode* node = stack.top();
            stack.pop();

            if (node->getRight() != nullptr) {
                stack.push(node->getRight());
            }
            if (node->getLeft() != nullptr) { 
                stack.push(node->getLeft()); 
            }

            //Ausgabe (könnte besser aussehen)

            cout    << setw(3) << left << node->getNodeID() << "|"
                    << setw(12) <<left << node->getName() << "|"
                    << setw(7) << right << node->getAlter() << "|"
                    << setw(11) << right << node->getEinkommen() << "|"
                    << setw(7) << right << node->getPLZ() << "|"
                    << setw(7) << left << node->getNodePosID() 
                    << endl;
            
        
        }
    }
};

//
////////////////////////////////////
