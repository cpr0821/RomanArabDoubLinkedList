#include "LinkedList.h"

LinkedList::LinkedList()
{
   //ctor
}

LinkedList::~LinkedList()
{
   //deletes linked list
}

LinkedList :: void print(fstream& file)
{
   if (headptr == nullptr)
   {
      return;
   }
   else
      file << headptr;

   LL.print(headptr->getNext(), file);
}

LinkedList::LinkedList& operator+=(DoubleLinkNode& newnode)
{
   tailptr->setNext(&newnode);
   tailptr->setPrev(tailptr);
   tailptr = &newnode;
   return *this;

}

