#ifndef Helper_H
#define HELPER_H

#include <string>
#include <string.h>
#include <vector>

using std::string;
using std::vector;

// a method to get size of an array
// template <typename T,unsigned S>
// inline unsigned arraysize(const T (&v)[S]) { return S; }

// method to be called at exit (example: free up pointers)
void cleanup(); 

// trim string of start and end delimeters
string trimString(string s, const char delimeters[]); 

// for debugging purposes. given a string, prints it's ASCII integer values
void viewStringAsASCII(string s); 

//check if 2 vectors are equal
template <class T>
bool vectors_equal(vector<T> v1, vector<T> v2){
  // needs to be implemented here since it uses templates
  return (v1.size() == v2.size() && std::equal(v1.begin(), v1.end(), v2.begin()));
}

#endif // HELPER_H