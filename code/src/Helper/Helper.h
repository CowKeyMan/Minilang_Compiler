#include <string>
#include <string.h>

using std::string;

// a method to get size of an array
template <typename T,unsigned S>
inline unsigned arraysize(const T (&v)[S]) { return S; }

void cleanup(); // method to be called at exit (example: free up pointers)

string trimString(string s, const char delimeters[]); // trim string of start and end delimeters

void viewStringAsASCII(string s); // for debugging purposes (detected CRLF)