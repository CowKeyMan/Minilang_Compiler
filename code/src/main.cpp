#include "Helper/helper.h"
#include "Lexer/Lexer.h"

#include <iostream>
#include <fstream>

#define TEST_LEXER
#define FILENAME "InputFiles/LexerTestInput.txt"

using std::cout;
using std::cerr;
using std::string;
using std::istreambuf_iterator;
using std::ifstream;
using std::unique_ptr;

// read the file specified by the filename and assign it to s
void readFile(string &s);

unique_ptr<string> file;
unique_ptr<Lexer> lexer;

int main(){
  atexit(cleanup);
  // Lexer
  file = unique_ptr<string>( new string() );
  readFile(*file);
  
  lexer = unique_ptr<Lexer>( new Lexer(*file) );
  lexer->lex();
#ifdef TEST_LEXER
  lexer->printTokens(); // for debugging purposes
#endif
  file.reset();
  lexer.reset(); // freeing pointer optimistions

  // Parser
  
}

void readFile(string &s){

  ifstream ifs(FILENAME);

  if(ifs){ // if the file was read properly
    string str((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    s = str;
  }else{
    // if the file could not be read report the error and exit
    cerr << "Error, could not read file\n";
    exit(EXIT_FAILURE);
  }
}
