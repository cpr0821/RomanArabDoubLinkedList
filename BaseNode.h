// Camryn Rogers
// cpr170030

#ifndef BASENODE_H
#define BASENODE_H
#include <string>
#include <fstream>
using namespace std;

class BaseNode
{
   public:
      BaseNode() {roman = "0"; arabic = 0;}
      BaseNode(string romanff, int arabicff) {roman = romanff; arabic = arabicff;}
      BaseNode (const BaseNode& node) {roman = node.roman; arabic = node.arabic;}
      int getArabic() const {return arabic;}
      string getRoman() const {return roman;}
      void setArabic(int arabicff) {arabic = arabicff;}
      void setRoman(string romanff) {roman = romanff;}
      friend ostream& operator<<(ostream& os, const BaseNode& node);
      friend istream& operator>>(istream& is, BaseNode& node);
      virtual ~BaseNode();

   protected:
      string roman;
      int arabic;
};

#endif // BASENODE_H
