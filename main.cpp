// Camryn Rogers
// cpr170030
// OVERLOADED OP LINES: 64,67,73,79, 22 of LinkedList.cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "BaseNode.h"
#include "DoubleLinkNode.h"
#include "LinkedList.h"

using namespace std;

// Function prototypes, included so main() can be written before these functions
void createLinkedList (LinkedList& LL); // this needs to create a linked list object and do it's stuff
void toRoman(LinkedList LL);
void toArabic(LinkedList LL);
bool Search(LinkedList LL, string value);
void bubble(LinkedList LL);

// Main driver function
int main()
{
// Create the linked list object
LinkedList LL;

int choice;                // The choice (1-3) for the menu
int sortChoice;            // The choice of which sort to perform (A v R)
string value;              // The value that the search is looking for or adding to list
fstream file;              // The file stream object for the file that will be evaluated (numbers.txt)

createLinkedList (LL);      // Fills in the linked list
//cout << "Linked List successfully created" << endl;
toRoman (LL);               // Converts Arabic to Roman numerals in the nodes
//cout << "toRoman complete" << endl;
toArabic (LL);              // Converts Roman to Arabic in the nodes
//cout << "toArabic complete" << endl;

   do
   {
   // Displays the menu and selects option (user input)
   cout << "Please enter a number.\n" << "1. Search\n2. Add\n3. Delete first\n4. Delete last\n5. Exit\n";
   cin >> choice;

      // If the user chooses to search, it asks for a value to search for
      if (choice == 1)
      {
         cout << "Please enter a value to search for (either Roman or Arabic)\n";
         cin >> value;

         // Calls search function to search list for value and displays message stating whether it was found or not
         if (Search(LL, value))
            cout << value << " was found\n";
         else
            cout << value << " was not found\n";
      }

      // If the user chooses to add, add to end of list
      if (choice == 2)
      {
      DoubleLinkNode newNode;

      cout << "Please enter the Arabic or Roman numeral that you would like to add:\n";
      cin >> newNode;

      //use += overloaded operator for LL to add linked list
      LL += newNode;
      }

      if (choice == 3)
      {
      //use --LL overloaded operator for LL object to delete fist item in list
      --LL;
      }

      if (choice == 4)
      {
      //use LL-- overloaded operator for LL object to delete last item in list
      LL--;
      }

      // If they choose option 5, program stops and information is written back to the file (happens after 1 and 2 as well)
      if (choice == 5)
      {
      file.open("numbers.txt", ios::out);

      // Call sort then recursive print from LL class
      bubble(LL);
      LL.print(LL.getHeadptr(), file);
      file.close();
      }

   } while (choice !=5);

   return 0;
} // End main function


void toArabic(LinkedList LL)
{
   //cout << "To Arabic:" << endl;
   // While the list has stuff in it
   while (LL.getHeadptr() != nullptr)
   {
      int sum = 0;
      int arabVal = LL.getHeadptr()->getArabic();
      //cout << "Arabic value: " << arabVal << endl;
      if (arabVal == 0)
      {
         //cout << "Arabic value is 0, need to convert to arabic" << endl;
         // Goes through the entire Roman Numeral string
         string roman = LL.getHeadptr()->getRoman();
         //cout << "This is the roman string: " << roman << endl;
         for (unsigned int i = 0; i < roman.length(); i++)
         {
            if (roman[i] == 'M')                                                          // If the letter is an M, add 1000 to the total sum
            sum +=1000;

            else if (roman[i] == 'D')                                                     // If the letter is an D, add 500 to the total sum
            sum +=500;

            else if (roman[i] == 'C' && (roman[i+1] == 'M' || roman[i+1] == 'D'))   // If the letter is a C and it's followed by an M or D, subtract 100 to the total sum
            sum -= 100;

            else if (roman[i] == 'C')                                                     // If the letter is a C, add 100 to the total sum
            sum +=100;

            else if (roman[i] == 'L')                                                     // If the letter is a L, add 50 to the total sum
            sum +=50;

            else if (roman[i] == 'X' && (roman[i+1] == 'L' || roman[i+1] == 'C'))   // If the letter is an X and the letter after it is a L or a C, subtract 10 from the total sum
            sum -= 10;

            else if (roman[i] == 'X')                                                     // If the letter is a X, add 10 to the total sum
            sum +=10;

            else if (roman[i] == 'V')                                                     // If the letter is a V, add 5 to the total sum
            sum +=5;

            else if (roman[i] == 'I' && (roman[i+1] == 'X' || roman[i+1] == 'V'))   // If the letter is an I and it's followed by a X or a V, subtract 1 from the total sum
            sum -= 1;

            else if (roman[i] == 'I')                                                     // If the letter is an I, add 1 to the total sum
            sum +=1;
         }
     //    cout << "This is the sum: " << sum << endl;
         LL.getHeadptr()->setArabic(sum);
       //  cout << "This is what is now in arabic for the node: ";
         int arabicnow = LL.getHeadptr()->getArabic();
         //cout << arabicnow << endl;
      }
      DoubleLinkNode* next = LL.getHeadptr()->getNext();
      LL.setHeadptr(next);// Return the total sum (which will end up being the Arabic equivalent of the Roman string)to the main function
   }
} // End toArabic()

void toRoman(LinkedList LL)
{
   //cout << "To Roman: " << endl;
   while (LL.getHeadptr() != nullptr)
   {
      string romanNum;
      string roman;
      roman = LL.getHeadptr()->getRoman();
    //  cout  << "This is the roman numeral: " << roman << endl;
      if(roman == "0")
      {
         //cout << "Roman num is 0, need to convert to Roman" << endl;
         int arabic = LL.getHeadptr() -> getArabic();
         //cout << "This is the arabic number being converted: " << arabic << endl;

         int thousands = arabic/1000;         // The number of thousands the Arabic number has
         int hundreds = (arabic%1000)/100;      // The number of hundreds the Arabic number has
         int tens = ((arabic%1000)%100)/10;     // The number of tens the Arabic number has
         int ones = ((arabic%1000)%100)%10;     // The number of ones the Arabic number has

         // Thousands and hundreds
         if (thousands > 0 && thousands <= 4)      // If there are more than zero and four or less thousands, add a M per thousand to the string
            for (int i = 1; i <= thousands; i++)
               romanNum += "M";

         if (hundreds > 0 && hundreds < 4)         // If there are more than zero and less than four hundreds, add a C per hundred to the string
            for (int i = 1; i <= hundreds; i++)
                  romanNum += "C";

         else if (hundreds == 4)                   // If there are four hundreds, add a CD to the string
               romanNum += "CD";

         else if (hundreds == 5)                   // If there are five hundreds, add a D to the string
            romanNum += "D";

         else if (hundreds > 5 && hundreds < 9)    // If there are more than five and less than nine hundreds, add a single D and a C per hundred to the string
         {
            romanNum += "D";
         for (int i = 6; i <= hundreds; i++)
            romanNum += "C";
         }
         else if (hundreds == 9)                   // If there are nine hundreds, add CM to the string
            romanNum += "CM";

         // Tens
         if (tens > 0 && tens < 4)                    // If there are more than zero and less than four tens, add a X per ten to the end of the string
            for (int i = 1; i <= tens; i++)
               romanNum += "X";

         else if (tens == 4)                       // If there are four tens, add a XL to the end of the string
            romanNum += "XL";

         else if (tens == 5)                       // IF there are five tens, add a L to the end of the string
            romanNum += "L";

         else if (tens > 5 && tens < 9)            // If there are more than five and less than nine tens, add a single L and a X per ten to the end of the string
         {
            romanNum += "L";
            for (int i = 6; i <= tens; i++)
            romanNum += "X";
         }
         else if (tens == 9)                       // If there are nine tens, add a XC to the end of the string
            romanNum += "XC";

      // Ones
         if (ones > 0 && ones < 4)                 // If there are more than zero and less than four ones, add an I per one to the end of the string
            for (int i = 1; i <= ones; i++)
               romanNum += "I";

         else if (ones == 4)                       // If there are four ones, add a IV to the end of the string
            romanNum += "IV";

         else if (ones == 5)                       // If there are five ones, add a V to the end of the string
            romanNum += "V";

         else if (ones > 5 && ones < 9)            // If there are more than five and less than nine ones, add a single V and one I per one
         {
            romanNum += "V";
         for (int i = 6; i <= ones; i++)
            romanNum += "I";
         }
         else if (ones == 9)                       // If there are nine ones, add a IX to the end of the string
            romanNum += "IX";

     //    cout << "This is the roman numeral being stored: " << romanNum << endl;
         LL.getHeadptr()->setRoman(romanNum);
         string currroman = LL.getHeadptr()->getRoman();
      //   cout << "This is the roman numeral in the node now: " << currroman << endl;
      }
     // cout << "already roman, no conversion" << endl;
      DoubleLinkNode* next = LL.getHeadptr()->getNext();
      LL.setHeadptr(next);                          // Return the Roman numeral string to the main function
   }
} // End toRoman()

void createLinkedList (LinkedList& LL)
{
   //cout << "Create linked list: " << endl;
   fstream file;              // The file stream object for the file that will be evaluated (numbers.txt)
   file.open("numbers3.txt", ios::in);         // Opens the file named "numbers.txt" in input and output mode (can be read from and written to without closing and reopening file)

   char firstChar;      // The first character of the line being evaluated
   string romanNum;     // The string that holds the Roman numeral conversion of the given Arabic integer
   int arabicNum;       // The Arabic integer given in numbers.txt
   int position = 0;    // The position of the file pointer

   bool eof = false;    // The end of file flag
   int i = 0;           // Counter variable
   bool valid;          //

   if (file)                                          // If the file opens properly
   {
      while (!eof)                                    // While the file is still returning readable data
      {
         position = file.tellg();                     // Assigns the position variable the value of the file pointer
         firstChar = file.peek();                     // Checks the first character of the line to see if it's a space or not

         if (isalpha(firstChar) || firstChar == ' ')
         {
            DoubleLinkNode newNode;

            if (firstChar == ' ')                        // Since the first character is a space we know that the line must contain an Arabic number
            {
              // cout << "Arabic is present " << endl;
               file.seekp(position, ios:: beg);          // Place the file pointer "position" away from the beginning of the file, at the beginning of the line that we're on
               file.seekg(17L, ios::cur);                // Moves the file pointer ahead 17 bytes
               file >> arabicNum;
              // cout << "This is the arabic num: " << arabicNum << endl;

               // Validate Arabic input
               if (arabicNum < 1 || arabicNum > 4999 || !arabicNum)
                  {
                  file.ignore();
                  }
               // Assigns correct input to Arabic value
               else
                  {
                  newNode.setArabic(arabicNum);
                  int currarab = newNode.getArabic();
                 // cout << "This is what's in the node now (arab): " << currarab << endl;
                  }

                  //file.clear();                             // Clears the end of file flag so that if this is the last line of the file, the roman numeral will still be printed at the beginning of the line
                  file.seekp(position, ios::beg);           // Moves the file pointer back to the beginning of the line
            }

         else                                       // The first character is not a space so we know that the line contains a roman numeral
         {
            file.seekg(position, ios::beg);           // Places the file pointer "position" away from the beginning of the file, at the beginning of the line that we're on
            file >> romanNum;                         // Reads in the roman numeral
           // cout << "This is the roman numeral in the file: " << romanNum << endl;
            while (romanNum[i] != '\0')
            {
               // Validate Roman values
               if(romanNum[i] == 'I' || romanNum[i] == 'V' || romanNum[i] == 'X' || romanNum[i] == 'L' || romanNum[i] == 'C' || romanNum[i] == 'D' || romanNum[i] == 'M')
                  valid = true;
               else
                  valid = false;
            i++;
            }
            if (valid)
            {
               newNode.setRoman(romanNum);
               string currroman = newNode.getRoman();
               //cout << "This is now in the node for roman: " <<currroman << endl;
            }
            else
               {
               file.ignore();
               }

            file.seekp(position,ios::beg);            // Puts the file pointer back at the beginning of the line
            file.seekp(17L, ios::cur);                // Moves ahead 17 bytes
         }

         // Adds nodes to list
         LL += newNode;

         eof = file.eof();                            // Sets "eof" to true if the end of the file has been reached
         position += 23;                              // Add 22 to the position variable, affectively moving the file pointer to the beginning of the next line (20 bytes for characters, one for newline character, one more to get to the next line)
         file.seekp(position, ios::beg);              // Put the file pointer at the beginning of the next line using the position variable, we do this here so that the position will be equal to the file pointer position
         }
         else
            return;
      }
   }
   file.close();
}

bool Search(LinkedList LL, string value)
{
// Stores Arabic value to search for
int arabVal;

// While the list has values in it
   while (LL.getHeadptr())
   {
      // If it's a roman numeral and it equals the value, found
      if(isalpha(value[0]))
      {
         while (LL.getHeadptr())
         {
            if (LL.getHeadptr()->getRoman() == value)
            {
               return true;
            }
            else
               LL.setHeadptr(LL.getHeadptr()->getNext());
         }
      }
   // Else convert string to int and compare Arabic numbers through the entire list
      else
      {
         arabVal = stoi(value);
         while (LL.getHeadptr())
         {
            if (LL.getHeadptr()->getArabic() == arabVal)
            {
               return true;
            }
         // Increment head
         LL.setHeadptr(LL.getHeadptr()->getNext());
         }
      }
      return false;
   }
}

void bubble(LinkedList LL)
{

int i,j, counter;

   while (LL.getHeadptr())
   {
      counter++;
   }

   for (i = 0; i < counter - 1; i++)
   {
      for (j = 0; j < counter - i - 1; j++)
      {
         if (LL.getHeadptr()->getArabic() > LL.getHeadptr()->getNext()->getArabic())
         {
            LL.getHeadptr()->setNext(LL.getHeadptr()->getNext());
            LL.getHeadptr()->getNext()->setNext(LL.getHeadptr());
            LL.getHeadptr()->getNext()->setPrev(LL.getHeadptr()->getPrev());
            LL.getHeadptr()->setPrev(LL.getHeadptr()->getNext());
            LL.setHeadptr(LL.getHeadptr()->getNext());
         }

      }
   }

}


