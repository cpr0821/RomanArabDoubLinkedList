// Camryn Rogers
// cpr170030

#ifndef DOUBLELINKNODE_H
#define DOUBLELINKNODE_H
#include "BaseNode.h"

class DoubleLinkNode : public BaseNode
{
   public:
      DoubleLinkNode();
      ~DoubleLinkNode();
      DoubleLinkNode(const BaseNode& node) : BaseNode(node) {}
      DoubleLinkNode(string romanff, int arabicff) : BaseNode(romanff, arabicff) {}
      DoubleLinkNode* getNext() const {return next;}
      DoubleLinkNode* getPrev() const {return prev;}
      void setNext(DoubleLinkNode* node) {next = node;}
      void setPrev(DoubleLinkNode* node) {prev = node;}

   private:
      DoubleLinkNode* next;
      DoubleLinkNode* prev;
};

#endif // DOUBLELINKNODE_H

