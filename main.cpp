// Camryn Rogers (cpr170030)

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <iomanip>

using namespace std;

// Prototypes for functions
bool validRows(char *board, fstream& output);
bool validCols(char *board, fstream& output);
bool validTBT(char *board, fstream& output);
bool spaces(char *board);


int main()
{
   int puzzleNum;                            // The number that identifies the puzzle
   fstream file;                             // The input file
   fstream output;                           // The output file
   int sizeArray = 90;                       // The size of the array (90 because 9x9=81 plus one newline for each line)
   char *board = new char[sizeArray];        // The pointer to the array

   // Open the input and output files
   file.open("puzzles3.txt", ios::in);
   output.open("solutions.txt", ios::out);

   // If the file opens properly
   if (file.good())
   {
         // Keep running until the end of the file
         while (!file.eof())
         {
            // Extract the first line, the puzzle number and display it in the output file
            file >> puzzleNum;
            output << puzzleNum << "\t";

            // Read in the next 9 lines of code into the dynamically allocated 1D array
            for (int i = 0; i <= sizeArray; i++)
             {
                *board = file.get();
                board++;
             }
             // Takes the pointer back to the beginning of the 9x9 puzzle
             board -= sizeArray;

             // If the rows, columns, and 3x3 grids have no duplicates it's valid, if it valid and has no spaces, it's solved
             if (validRows(board, output) && validCols(board, output) && validTBT(board, output))
             {
               if(spaces(board))
                  output << "valid";
               else
                  output << "solved";
             }
             output << endl;
         }
   }

   // Close the files
   file.close();
   output.close();
   return 0;
}

// Checks to make sure that the rows of the 9x9 puzzles do not contain duplicates, returns true or false
bool validRows(char *board, fstream& output)
{
char currNum = *board;     // The current number being compared is the first element in the array being pointed to
char *begPos;              // The beginning position
int colSize = 9;           // The size of the columns
int numRows = 9;           // The number of rows
begPos = board;            // The beginning address is set to the initial position of the pointer
board++;                   // The pointer is moved ahead one space (so it does not compare it to itself)

// Goes through all 9 rows
for (int j = 1; j <= numRows; j++)
{
   // Moves the current number by one element after the previous element is compared to the whole row
   for (int moveInRow = 1; moveInRow < colSize; moveInRow++)
   {
      // Compares one current number to the rest of the row
      for(int i = moveInRow + 1; i <= colSize; i++)
      {
         // If the current number being compared is the same as an element in that row, it's a duplicate and the function returns false (not valid) and an error message describing where the duplicate is
         if (currNum == *board && currNum != ' ' && currNum != '\n')
         {
            output << "invalid\t  there are two " << *board << "s in row " << j << endl;
            return false;
         }
         // Otherwise it moves to the next element in the line
         else
            board++;
      }
   // The board pointer is set to the initial position plus the position of the previous "current number" to move the current number by one, then the board position is moved to be on the right of that one so it does not compare to itself
   board = begPos + moveInRow;
   currNum = *board;
   board++;
   }
// To move the row you set the pointer to its initial location and add 10, set the first one as your current number and add one to the board pointer to get it to the right of that one
board = begPos + (10 * j);
currNum = *board;
board++;
}

// If it gets through the 9x9 without finding a duplicate, it returns that the rows are valid
return true;
}

// Checks to make sure that the columns of the 9x9 puzzles do not contain duplicates, returns true or false
bool validCols(char *board, fstream& output)
{
int numRows = 9;           // Number of rows
int numCols = 9;           // Number of columns
char currVal = *board;     // The current value being compared is the initial board pointer location
char *begPos;              // The beginning position
begPos = board;            // Setting up the initial position
board += 10;               // Adds 10 to the board pointer to get to the element below the first "current number"

// Goes through all 9 columns
for (int j = 0; j < numCols; j++)
{
   // Moves the "current number" through the column
   for (int row = 1; row < numRows; row++)
   {
      // Compares each remaining element in column to the current number
      for(int i = row + 1; i <= numCols; i++)
      {
         // If there are duplicates, return false, otherwise increment by 10 to get to the next element to compare to
         if (currVal == *board && currVal != ' ' && currVal != '\n')
         {
            output << "invalid\t  there are two " << *board << "s in column " << j + 1 << endl;
            return false;
         }
         else
            board += 10;
      }
   // Moves current number by one
   board = begPos + (10 * row) + j;
   currVal = *board;
   board += 10;
   }
// Moves to the next column
board = begPos + j;
currVal = *board;
board += 10;
}

// If there are no duplicates, return true (valid columns)
return true;
}



bool validTBT(char *board, fstream& output)
{
int numRows = 3;           // Number of rows being evaluated at once
int numCols = 3;           // Number of columns being evaluated at once
int tbts = 9;              // Number of 3x3 puzzles
char currVal = *board;     // The current value being compared if the first element in the puzzle (row 1 col 1)
char *begPos;              // The beginning position variable
begPos = board;            // The address to the beginning is being stored in begPos
board++;                   // The board position is incremented by one the get to the right of the currently evaluated character

// Goes through all 3x3 puzzles (there are 9 of them)
for (int i = 1; i <= tbts; i++)
{
   // Goes through the sections of the rows
   for (int j = 1; j < numRows; j++)
   {
      // Moves the current value being evaluated
      for (int k = (j + 1); k < numCols; k++)
      {
         // If a duplicate is found, print out an error message
         if ((currVal == *board) && (currVal != ' ') && (currVal != '\n'))
         {
            cout << currVal << " " << *board << endl;
            cout << currVal << " " << *board << endl;
            output << "invalid\t  there are two " << *board << "s in the ";
            if (i == 0)
               output << "top left 3x3 grid" << endl;
            if (i == 1)
               output << "top mid 3x3 grid" << endl;
            if (i == 2)
               output << "top right 3x3 grid" << endl;
            if (i == 3)
               output << "mid left 3x3 grid" << endl;
            if (i == 4)
               output << "mid mid 3x3 grid" << endl;
            if (i == 5)
               output << "mid right 3x3 grid" << endl;
            if (i == 6)
               output << "bottom left 3x3 grid" << endl;
            if (i == 7)
               output << "bottom mid 3x3 grid" << endl;
            if (i == 8)
               output << "bottom right 3x3 grid" << endl;
            return false;
         }
         else
            board++;
      }
      // To move the number being evaluated, the position needs to be moved by the number of times it's iterated (1 or 2 since it's limited to < 3)
      board = (begPos + j);
      currVal = *board;
      board++;
   }
   // To get to the next 3x3, the pointer needs to move 3 from the beginning
   board = begPos + 3;
   currVal = *board;
   board++;
}

return true;
}

// Checks to see if the 9x9 has any spaces
bool spaces (char *board)
{
   int sizeArray = 90;                    // The size of the 9x9 puzzle

   // Goes through the entire array and if an element is a space then it returns true
   for (int i =0; i < sizeArray; i++)
   {
      if (*board == ' ')
         return true;
      else
         board++;
  }
  // Otherwise is returns false
  return false;
}





