#include "BaseNode.h"

BaseNode::BaseNode()
{
   //ctor
}

BaseNode::~BaseNode()
{
   //dtor
}

BaseNode :: ostream& operator<<(ostream& os, const BaseNode* node)
{

os << setw(17) << left << node.roman << setw(4) << node.arabic << endl;
return os;

}

BaseNode :: istream& operator>>(istream& is, const BaseNode& node)
{

is >> node.roman >> node.arabic;
return is;

}

