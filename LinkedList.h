// Camryn Rogers
// cpr170030

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "DoubleLinkNode.h"


class LinkedList
{
   public:
      LinkedList() {headptr = nullptr; tailptr = nullptr;}
      LinkedList(DoubleLinkNode node) {}
      DoubleLinkNode* getHeadptr() const {return headptr;}
      DoubleLinkNode* getTailptr()const {return tailptr;}
      void setHeadptr(DoubleLinkNode* node) {headptr = node;}
      void setTailptr(DoubleLinkNode* node) {tailptr = node;}
      void print(DoubleLinkNode* head, fstream& file);
      LinkedList& operator+=(DoubleLinkNode& newnode);
      void operator--() {this->setHeadptr(this->getHeadptr()->getNext()); delete this->getHeadptr()->getPrev(); this->getHeadptr()->setPrev(nullptr);}
      void operator--(int) {this->setTailptr(this->getTailptr()->getPrev()); delete this->getTailptr()->getNext(); this->getTailptr()->setNext(nullptr);}
      ~LinkedList();

   private:
      DoubleLinkNode* headptr;
      DoubleLinkNode* tailptr;

};

#endif // LINKEDLIST_H

