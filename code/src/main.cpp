#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#include "Helper/helper.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

#define TEST_LEXER
#define FILENAME "InputFiles/Input.txt"

using std::cout;
using std::cerr;
using std::string;
using std::istreambuf_iterator;
using std::ifstream;
using std::unique_ptr;
using std::vector;

// read the file specified by the filename and assign it to s
void readFile(string &s);

unique_ptr<string> file;
unique_ptr<Lexer> lexer;
unique_ptr<Parser> parser;

vector<Token> tokens;

int main(){
  // Lexer
  file = unique_ptr<string>( new string() );
  readFile(*file);
  
  lexer = unique_ptr<Lexer>( new Lexer(*file) );
  lexer->lex();
  lexer->removeComments();
  tokens = lexer->get_tokens();
#ifdef TEST_LEXER
  lexer->printTokens(); // for debugging purposes
#endif
  file.reset();
  lexer.reset(); // freeing pointer optimistions

  //DELETE COMMENTS

  // Parser
  parser = unique_ptr<Parser>( new Parser(&tokens) );

  bool successParse = parser->parse();
  cout << (successParse? 1 : 0) << "\n";
  cout << "hello\n";
  if(successParse){
    XMLVisitor *x = new XMLVisitor();
    ASTNode* tree = parser->getTree();
    tree->accept(x);
    x->trimXMLNewLines();
    cout << x->getXML();
  }

  parser.reset(); // freeing pointer optimistions
  tokens = vector<Token>(); // reset tokens vector to free up memory

  return 0;

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
