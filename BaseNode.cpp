// Camryn Rogers
// cpr170030

#include "BaseNode.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;


BaseNode::~BaseNode()
{
   //dtor
}

//Prints out a node
ostream&operator<<(ostream& os, const BaseNode& node)
{
os << setw(17) << left << node.getRoman() << setw(4) << node.getArabic() << endl;
return os;
}

//Takes a value from the user and puts it in a node along with its counterpart
istream& operator>>(istream& is, BaseNode& node)
{
   string value;
   int arabVal, sum;

   is >> value;

         // If it's a roman numeral, find counterpart and add to node
         if(isalpha(value[0]))
         {
            for (int i = 0; i < value.length(); i++)
            {
               if (value[i] == 'M')                                                          // If the letter is an M, add 1000 to the total sum
               sum +=1000;

               else if (value[i] == 'D')                                                     // If the letter is an D, add 500 to the total sum
               sum +=500;

               else if (value[i] == 'C' && (value[i+1] == 'M' || value[i+1] == 'D'))   // If the letter is a C and it's followed by an M or D, subtract 100 to the total sum
               sum -= 100;

               else if (value[i] == 'C')                                                     // If the letter is a C, add 100 to the total sum
               sum +=100;

               else if (value[i] == 'L')                                                     // If the letter is a L, add 50 to the total sum
               sum +=50;

               else if (value[i] == 'X' && (value[i+1] == 'L' || value[i+1] == 'C'))   // If the letter is an X and the letter after it is a L or a C, subtract 10 from the total sum
               sum -= 10;

               else if (value[i] == 'X')                                                     // If the letter is a X, add 10 to the total sum
               sum +=10;

               else if (value[i] == 'V')                                                     // If the letter is a V, add 5 to the total sum
               sum +=5;

               else if (value[i] == 'I' && (value[i+1] == 'X' || value[i+1] == 'V'))   // If the letter is an I and it's followed by a X or a V, subtract 1 from the total sum
               sum -= 1;

               else if (value[i] == 'I')                                                     // If the letter is an I, add 1 to the total sum
               sum +=1;
            }
            arabVal = sum;
         }

         // Else it's an Arabic number, find counterpart and add to node
         else
         {
            arabVal = stoi(value);
            value = "";

            int thousands = arabVal/1000;         // The number of thousands the Arabic number has
            int hundreds = (arabVal%1000)/100;      // The number of hundreds the Arabic number has
            int tens = ((arabVal%1000)%100)/10;     // The number of tens the Arabic number has
            int ones = ((arabVal%1000)%100)%10;     // The number of ones the Arabic number has

            // Thousands and hundreds
            if (thousands > 0 && thousands <= 4)      // If there are more than zero and four or less thousands, add a M per thousand to the string
               for (int i = 1; i <= thousands; i++)
                  value += "M";

            if (hundreds > 0 && hundreds < 4)         // If there are more than zero and less than four hundreds, add a C per hundred to the string
               for (int i = 1; i <= hundreds; i++)
                  value += "C";

            else if (hundreds == 4)                   // If there are four hundreds, add a CD to the string
               value += "CD";

            else if (hundreds == 5)                   // If there are five hundreds, add a D to the string
               value += "D";

            else if (hundreds > 5 && hundreds < 9)    // If there are more than five and less than nine hundreds, add a single D and a C per hundred to the string
            {
               value += "D";
            for (int i = 6; i <= hundreds; i++)
               value += "C";
            }
            else if (hundreds == 9)                   // If there are nine hundreds, add CM to the string
               value += "CM";

            // Tens
            if (tens > 0 && tens < 4)                    // If there are more than zero and less than four tens, add a X per ten to the end of the string
               for (int i = 1; i <= tens; i++)
                  value += "X";

            else if (tens == 4)                       // If there are four tens, add a XL to the end of the string
               value += "XL";

            else if (tens == 5)                       // IF there are five tens, add a L to the end of the string
               value += "L";

            else if (tens > 5 && tens < 9)            // If there are more than five and less than nine tens, add a single L and a X per ten to the end of the string
            {
               value += "L";
               for (int i = 6; i <= tens; i++)
               value += "X";
            }
            else if (tens == 9)                       // If there are nine tens, add a XC to the end of the string
               value += "XC";

         // Ones
            if (ones > 0 && ones < 4)                 // If there are more than zero and less than four ones, add an I per one to the end of the string
               for (int i = 1; i <= ones; i++)
                  value += "I";

            else if (ones == 4)                       // If there are four ones, add a IV to the end of the string
               value += "IV";

            else if (ones == 5)                       // If there are five ones, add a V to the end of the string
               value += "V";

            else if (ones > 5 && ones < 9)            // If there are more than five and less than nine ones, add a single V and one I per one
            {
               value += "V";
            for (int i = 6; i <= ones; i++)
               value += "I";
            }
            else if (ones == 9)                       // If there are nine ones, add a IX to the end of the string
               value += "IX";
         }
         node.setArabic(arabVal);
         node.setRoman(value);

return is;
}
