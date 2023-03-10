#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void reader_program () {
  // Create a text file
  //ofstream MyWriteFile("MC-file-list.txt");

  // Write to the file
//  MyWriteFile << "Files can be tricky, but it is fun enough!";

  // Close the file
  //MyWriteFile.close();

  // Create a text string, which is used to output the text file
  string myText;

  // Read from the text file
  ifstream MyReadFile("MC-file-list.txt");

  // Use a while loop together with the getline() function to read the file line by line
  while (getline (MyReadFile, myText)) {
    // Output the text from the file
    cout << myText;
  }

  // Close the file
  MyReadFile.close();
}
