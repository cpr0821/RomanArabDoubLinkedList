// Camryn Rogers
// cpr170030

#include "LinkedList.h"
#include <iostream>

LinkedList::~LinkedList()
{
   //deletes linked list
}

// Prints the linked list recursively
void LinkedList :: print(DoubleLinkNode* head, fstream& file)
{
   if (head == tailptr->getNext())
   {
      //cout << "null" << endl;
      return;
   }
   else
   {
      file << head;
      print(head->getNext(), file);
   }
}

// Adds a node to the end of the linked list
LinkedList& LinkedList :: operator+=(DoubleLinkNode& newnode)
{
   //If it's the first one, set head
      if (headptr == nullptr)
         {
            //cout << "true" << endl;
            headptr = &newnode;
            headptr->setPrev(nullptr);
            tailptr = &newnode;
            //cout << " tail value: " << *tailptr << endl;
            //cout  << " head value: " << *headptr << endl;
         }
   //Else add the node at the end and adjust the tail
      else
         {
            //cout << "false" << endl;
            tailptr->setNext(&newnode);
            tailptr = &newnode;
            tailptr->setPrev(tailptr);
            tailptr->setNext(nullptr);
            //cout << "tail value: " << *tailptr << endl;
            //cout  << "head value: " << *headptr << endl;
         }

   return *this;

}

